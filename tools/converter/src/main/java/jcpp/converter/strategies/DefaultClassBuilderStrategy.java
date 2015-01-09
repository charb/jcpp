package jcpp.converter.strategies;

import jcpp.converter.model.*;
import java.util.*;
import org.objectweb.asm.*;

public class DefaultClassBuilderStrategy implements IClassBuilderStrategy{

	public DefaultClassBuilderStrategy(){
	}	

	public String getMacroExport(){
		return "JCPP_EXPORT";
	}

	public void initialize(CPPClass clazz){
		clazz.setName(getClassName(clazz.getJavaClassName()));
		clazz.getType().setNamespaces(clazz.getPackage().getNamespaces());
		clazz.setSuperClass(getCPPType(clazz.getSuperJavaClassName()));
		for (String s: clazz.getInterfacesJavaClassName()){
			clazz.addInterface(getCPPType(s));
		}
		clazz.getHeader().setCPPFileName(clazz.getName()+".h");
		clazz.getSource().setCPPFileName(clazz.getName()+".cpp");
		clazz.getHeader().setIfDefName(getIfDefName(clazz));
	}

	//returns the macro name from the class name
	public String getIfDefName(CPPClass clazz){
		List<String> ns=clazz.getNamespaces();
		String s="";
		for (String n : ns){
			s+=n.toUpperCase()+"_";
		}
		s+=clazz.getName().toUpperCase()+"_H";
		return s;
	}

	//returns the CPP classname from the simple class name
	protected String getClassName(String n){
		return "J"+n;
	}

	//returns namespaces from the java class name
	public List<String> getNamespaces(String className){
		List<String> ns=new ArrayList<String>();
		StringTokenizer stk=new StringTokenizer(className,".");
		while (stk.hasMoreElements()){
			String n=(String)stk.nextElement();
			ns.add(n);
		}
		ns.remove(ns.size()-1);
		return ns;
	}

	//returns the simple class name from the java class name
	public String getSimpleName(String className){
		int index=className.lastIndexOf(".");
		if (index>0){
			return className.substring(index+1);
		}
		return className;
	}

	//returns the CPPType from the bytecode type
	public CPPType getCPPType(Type type){
		if (type.getSort()==Type.ARRAY){
			CPPType elementType=getCPPType(type.getElementType());
			if (elementType==CPPType.BOOLEAN_TYPE){
				return CPPType.BOOLEAN_ARRAY_TYPE;
			
			}else if (elementType==CPPType.BYTE_TYPE){
				return CPPType.BYTE_ARRAY_TYPE;
			
			}else if (elementType==CPPType.CHAR_TYPE){
				return CPPType.CHAR_ARRAY_TYPE;
			
			}else if (elementType==CPPType.DOUBLE_TYPE){
				return CPPType.DOUBLE_ARRAY_TYPE;
			
			}else if (elementType==CPPType.FLOAT_TYPE){
				return CPPType.FLOAT_ARRAY_TYPE;
			
			}else if (elementType==CPPType.INT_TYPE){
				return CPPType.INT_ARRAY_TYPE;
			
			}else if (elementType==CPPType.LONG_TYPE){
				return CPPType.LONG_ARRAY_TYPE;
			
			}else if (elementType==CPPType.SHORT_TYPE){
				return CPPType.SHORT_ARRAY_TYPE;
			
			}else{
				return CPPType.getArrayType(elementType);
			}

		}else if (type.getSort()==Type.BOOLEAN){
			return CPPType.BOOLEAN_TYPE;

		}else if (type.getSort()==Type.BYTE){
			return CPPType.BYTE_TYPE;

		}else if (type.getSort()==Type.CHAR){
			return CPPType.CHAR_TYPE;

		}else if (type.getSort()==Type.DOUBLE){
			return CPPType.DOUBLE_TYPE;

		}else if (type.getSort()==Type.FLOAT){
			return CPPType.FLOAT_TYPE;

		}else if (type.getSort()==Type.INT){
			return CPPType.INT_TYPE;

		}else if (type.getSort()==Type.LONG){
			return CPPType.LONG_TYPE;

		}else if (type.getSort()==Type.OBJECT){
			CPPType cppType=new CPPType();
			cppType.setType(CPPType.Type.OBJECT);
			cppType.getNamespaces().addAll(getNamespaces(type.getClassName()));
			cppType.setName(getClassName(getSimpleName(type.getClassName())));
			return cppType;

		}else if (type.getSort()==Type.SHORT){
			return CPPType.SHORT_TYPE;

		}else if (type.getSort()==Type.VOID){
			return CPPType.VOID_TYPE;
		}
		throw new RuntimeException("Uknown type "+type);    
	}

	//TODO bugged, name can be like java.util.Map.Entry or Map.Entry
	//returns the CPPType from the java class name
	public CPPType getCPPType(String javaClassName){
		if (javaClassName==null){
			return null;
		}
		if (javaClassName.equals("Z")){
			return CPPType.BOOLEAN_TYPE;

		}else if (javaClassName.equals("B")){
			return CPPType.BYTE_TYPE;
		
		}else if (javaClassName.equals("C")){
			return CPPType.CHAR_TYPE;
		
		}else if (javaClassName.equals("S")){
			return CPPType.SHORT_TYPE;
		
		}else if (javaClassName.equals("I")){
			return CPPType.INT_TYPE;
		
		}else if (javaClassName.equals("J")){
			return CPPType.LONG_TYPE;
		
		}else if (javaClassName.equals("F")){
			return CPPType.FLOAT_TYPE;
		
		}else if (javaClassName.equals("D")){
			return CPPType.DOUBLE_TYPE;
		
		}else if (javaClassName.equals("V")){
			return CPPType.VOID_TYPE;
		
		}else if (javaClassName.equals("[Z")){
			return CPPType.BOOLEAN_ARRAY_TYPE;

		}else if (javaClassName.equals("[B")){
			return CPPType.BYTE_ARRAY_TYPE;
		
		}else if (javaClassName.equals("[C")){
			return CPPType.CHAR_ARRAY_TYPE;
		
		}else if (javaClassName.equals("[S")){
			return CPPType.SHORT_ARRAY_TYPE;
		
		}else if (javaClassName.equals("[I")){
			return CPPType.INT_ARRAY_TYPE;
		
		}else if (javaClassName.equals("[J")){
			return CPPType.LONG_ARRAY_TYPE;
		
		}else if (javaClassName.equals("[F")){
			return CPPType.FLOAT_ARRAY_TYPE;
		
		}else if (javaClassName.equals("[D")){
			return CPPType.DOUBLE_ARRAY_TYPE;
		
		}else if (javaClassName.charAt(0)=='['){
			CPPType elementType=getCPPType(javaClassName.substring(1,javaClassName.length()));
			return CPPType.getArrayType(elementType);

		}else{
			if (javaClassName.charAt(0)=='L' && javaClassName.charAt(javaClassName.length()-1)==';'){
				javaClassName=javaClassName.substring(1,javaClassName.length()-1);
			}
			javaClassName=javaClassName.replace('/','.');
			CPPType cppType=new CPPType();
			cppType.setType(CPPType.Type.OBJECT);
			cppType.getNamespaces().addAll(getNamespaces(javaClassName));
			cppType.setName(getClassName(getSimpleName(javaClassName)));
			return cppType;
		}
	}
}
package jcpp.converter.writer;

import jcpp.converter.strategies.*;
import jcpp.converter.model.*;
import java.io.*;
import java.util.*;

//TODO factorize all h/cpp writers in AbstractCPPWriter
public class CPPClassSourceWriter{
	protected IStrategies strategies;
	protected CPPClass clazz;
	protected CPPTypeWriter typeWriter;
	protected CPPMethodWriter methodWriter;

	public CPPClassSourceWriter(IStrategies strategies,CPPClass clazz){
		this.strategies=strategies;
		this.clazz=clazz;
		this.typeWriter=new CPPTypeWriter(strategies);
		this.methodWriter=new CPPMethodWriter(strategies);
	}

	public void write(File currentDir) throws Exception{
		File sourceFile=new File(currentDir,clazz.getSource().getCPPFileName());
		sourceFile.getParentFile().mkdirs();
		sourceFile.createNewFile();

		StringBuffer sb=new StringBuffer();

		writeIncludes(sb);
		writeUsingNamespaces(sb);

		String idnt=writeStartNamespace(sb);

		writeBody(idnt,sb);

		writeEndNamespace(sb);

		FileOutputStream fos=new FileOutputStream(sourceFile);
		fos.write(sb.toString().getBytes());
		fos.close();
	}

	protected void writeIncludes(StringBuffer sb){
		if (clazz.getSource().getIncludes().size()>0){
			for (CPPType type : clazz.getSource().getIncludes()){
				sb.append("#include \"").append(type.getIncludePath()).append("\"").append(System.lineSeparator());
			}
			sb.append(System.lineSeparator());
		}
	}

	protected void writeUsingNamespaces(StringBuffer sb){
		if (clazz.getSource().getUsings().size()>0){
			for (CPPType type : clazz.getSource().getUsings()){
				sb.append("using namespace ").append(type.getUsingNamespace()).append(";").append(System.lineSeparator());
			}
			sb.append(System.lineSeparator());
		}
	}

	protected String writeStartNamespace(StringBuffer sb){
		String indnt="";
		for (String ns : clazz.getNamespaces()){
			sb.append(indnt+"namespace "+ns+"{").append(System.lineSeparator());
			indnt+="    ";
		}
		return indnt;
	}

	protected void writeBody(String ident,StringBuffer sb)throws Exception{
		for (CPPMethod method : clazz.getSource().getMethods().values()){
			writeMethod(ident,sb,method);
		}

		writeDestructor(ident,sb);
	}

	protected void writeMethod(String ident, StringBuffer sb,CPPMethod method) throws Exception{
		sb.append(ident);
		typeWriter.write(method.getInfo().getReturnType(),sb);
		sb.append(" ").append(clazz.getName()).append("::").append(method.getInfo().getName()).append("(");
		int i=0;
		for (CPPType type : method.getInfo().getParameters()){
			if (i>0){
				sb.append(", ");
			}
			typeWriter.write(type,sb);
			if (method.getInfo().getParameterNames().size()>0){
				sb.append(" ").append(method.getInfo().getParameterNames().get(i));
			}else{
				sb.append(" p"+i);
			}
			i++;
		}
		sb.append("){");
		sb.append(System.lineSeparator());
		methodWriter.write(ident+"    ",method,sb);
		sb.append(ident).append("}");
		sb.append(System.lineSeparator());
		sb.append(System.lineSeparator());
	}

	//TODO shouldnt be treated differently than a normal method
	protected void writeDestructor(String ident, StringBuffer sb){
		sb.append(ident);
		sb.append(clazz.getName()).append("::~").append(clazz.getName()).append("(){}");
		sb.append(System.lineSeparator());
	}

	protected void writeEndNamespace(StringBuffer sb){
		for (int i=clazz.getNamespaces().size() ; i>0 ; i--){
			String indnt="";
			for (int j=0;j<i-1;j++){
				indnt+="    ";
			}
			sb.append(indnt+"}").append(System.lineSeparator());
		}
	}
}
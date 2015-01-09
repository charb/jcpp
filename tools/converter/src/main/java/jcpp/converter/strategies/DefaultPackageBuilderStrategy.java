package jcpp.converter.strategies;

import jcpp.converter.model.*;
import java.util.*;
import java.io.*;

public class DefaultPackageBuilderStrategy implements IPackageBuilderStrategy{
	protected Set<String> toSkip;

	public DefaultPackageBuilderStrategy(){
		toSkip=new HashSet<String>();
		toSkip.add("package-info.java");
		toSkip.add("Enum.java");
		toSkip.add("ValuedEnum.java");
		toSkip.add("EnumUtils.java");
		toSkip.add("AnnotationUtils.java");
		//TODO create config object for that read from file
	}

	//used to skip classes that we dont want to convert
	public boolean skipFile(File fileName){
		return toSkip.contains(fileName.getName());
	}

	public boolean skipFolder(File f){
		return false;
	}

	protected List<CPPType> getPackageDependencies(){
		List<CPPType> deps=new ArrayList<CPPType>();

		CPPType t1=new CPPType();
		t1.setType(CPPType.Type.OBJECT);
		t1.setName("JPackage");
		t1.addNamespace("jcpp");
		t1.addNamespace("lang");
		t1.addNamespace("reflect");
		deps.add(t1);

		CPPType t2=new CPPType();
		t2.setType(CPPType.Type.OBJECT);
		t2.setName("JList");
		t2.addNamespace("jcpp");
		t2.addNamespace("util");
		deps.add(t2);

		return deps;
	}

	public void initialize(CPPPackage pkge){
		pkge.setCPPFolderName(pkge.getJavaPackageName());
		String pkgeName=getPackageName(pkge);
		pkge.getHeader().setCPPFileName(pkgeName+".h");
		pkge.getSource().setCPPFileName(pkgeName+".cpp");
		pkge.setName(pkgeName);
		pkge.setJavaClassName(getClassName(pkge));
		pkge.getHeader().setIfDefName(pkgeName+"_H");
		for (String n : getNamespaces(pkge)){
			pkge.getType().addNamespace(n);
		}

		for (CPPType t : getPackageDependencies()){
			pkge.getHeader().addDependency(t);
		}

		CPPMethodInfo pkgeConstructor=new CPPMethodInfo(pkge);
		pkgeConstructor.setName(pkge.getName());
		pkgeConstructor.setProtected(true);
		pkgeConstructor.setConstructor(true);
		pkgeConstructor.setSignature(pkge.getName());
		pkge.getHeader().addMethod(pkgeConstructor);

		CPPMethodInfo methodGetPackage=new CPPMethodInfo(pkge);
		methodGetPackage.setName("getPackage");
		methodGetPackage.setStatic(true);
		methodGetPackage.setReturnType(pkge.getType());
		methodGetPackage.setSignature("getPackage");
		pkge.getHeader().addMethod(methodGetPackage);

		CPPMethodInfo methodGetSuperPackage=new CPPMethodInfo(pkge);
		methodGetSuperPackage.setName("getSuperPackage");
		CPPType pkgeType=new CPPType("JPackage",Arrays.asList("jcpp","lang"));
		methodGetSuperPackage.setReturnType(pkgeType);
		methodGetSuperPackage.setSignature("getSuperPackage");
		pkge.getHeader().addMethod(methodGetSuperPackage);		

		CPPMethodInfo methodGetPackages=new CPPMethodInfo(pkge);
		methodGetPackages.setName("getPackages");
		CPPType pkgeListType=new CPPType("JList",Arrays.asList("jcpp","util"));
		methodGetPackages.setReturnType(pkgeListType);
		methodGetPackages.setSignature("getPackages");
		pkge.getHeader().addMethod(methodGetPackages);

		pkge.setSuperClass(pkgeType);
	}

	//TODO add suffix to all created packages
	//used to create from the package name from the package object
	public String getPackageName(CPPPackage pkge){
		String s="";
		if (pkge.getParent()!=null){
	        for (String ns : getNamespaces(pkge.getParent())){
	            s+=ns.toUpperCase()+"_";
	        }
	    }
        return s+pkge.getJavaPackageName().toUpperCase()+"_PACKAGE";
	}

	//used to set the class name of the package
	//for the moment it is equal to the folder separated with .
	//exactly like the Java package
	public String getClassName(CPPPackage pkge){
		String s="";
        for (String ns : getNamespaces(pkge)){
            s+=ns+".";
        }
        s=s.substring(0,s.length()-1);
        return s;
	}

	//used to create the namespace of the package object
	//for the moment, it corresponds to the folder structure read from Java
	public List<String> getNamespaces(CPPPackage pkge){
		List<CPPPackage> parents=new ArrayList<CPPPackage>();
		List<String> ns=new ArrayList<String>();
		CPPPackage parent=pkge;
		parents.add(parent);
		while (parent.getParent()!=null){
			parent=parent.getParent();
			parents.add(parent);
		}
		for (int i=0;i<parents.size();i++){
			ns.add(parents.get(parents.size()-1-i).getJavaPackageName());
		}
		return ns;
	}
}
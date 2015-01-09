package jcpp.converter.builder;

import jcpp.converter.model.*;
import jcpp.converter.strategies.*;
import java.io.*;
import java.util.*;

public class CPPPackageBuilder{
	protected IStrategies strategies;
	protected CPPClassBuilder classBuilder;

	public CPPPackageBuilder(IStrategies strategies){
		this.strategies=strategies;
		this.classBuilder=new CPPClassBuilder(strategies);
	}

	public CPPPackage build(File byteFile,File sourceFile) throws Exception{
		return build(byteFile,sourceFile,null);
	}

	protected boolean skipFile(File fileName){
		return strategies.getPackageBuilderStrategy().skipFile(fileName);
	}

	protected boolean skipFolder(File fileName){
		return strategies.getPackageBuilderStrategy().skipFolder(fileName);
	}

	protected File getSourceFile(File child,File sourceFile){
		String name=child.getName();
		return new File(sourceFile,name.replaceAll(".class",".java"));
	}

	protected CPPPackage build(File byteFile,File sourceFile, CPPPackage parent) throws Exception{
		if (byteFile.isDirectory() && !skipFolder(sourceFile)){
			CPPPackage current=new CPPPackage();
			current.setJavaPackageName(byteFile.getName());
			if (parent!=null){
				current.setParent(parent);
			}
			strategies.getPackageBuilderStrategy().initialize(current);
			for (File f : byteFile.listFiles()) {
				build(f,getSourceFile(f,sourceFile),current);
			}
			current.setDependencies();
			return current;

		}else{
			if (!skipFile(sourceFile) && !sourceFile.getName().contains("$")) {
				classBuilder.build(parent,byteFile,sourceFile);
			}
			return parent;
		}
	}
}
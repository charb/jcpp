package jcpp.converter.writer;

import jcpp.converter.strategies.*;
import jcpp.converter.model.*;
import java.io.*;

public class CPPWriter{
	protected IStrategies strategies;
	protected CPPPackage root;

	public CPPWriter(IStrategies strategies,CPPPackage root){
		this.strategies=strategies;
		this.root=root;
	}

	public void write(File headerDir,File sourceDir) throws Exception{
		writeHeader(headerDir,root);
		writeSource(sourceDir,root);
	}

	protected void writeHeader(File headerDir, CPPPackage current) throws Exception{
		File currentDir=new File(headerDir,current.getCPPFolderName());
		if (!currentDir.exists()){
			currentDir.mkdirs();
		}
		(new CPPClassHeaderWriter(strategies,current)).write(currentDir);

		for (CPPClass c : current.getClasses()){
			(new CPPClassHeaderWriter(strategies,c)).write(currentDir);
		}

		for (CPPPackage p : current.getSubPackages()){
			writeHeader(currentDir,p);
		}
	}

	protected void writeSource(File sourceDir, CPPPackage current) throws Exception{
		File currentDir=new File(sourceDir,current.getCPPFolderName());
		if (!currentDir.exists()){
			currentDir.mkdirs();
		}
		(new CPPPackageSourceWriter(strategies,current)).write(currentDir);

		for (CPPClass c : current.getClasses()){
			(new CPPClassSourceWriter(strategies,c)).write(currentDir);
		}

		for (CPPPackage p : current.getSubPackages()){
			writeSource(currentDir,p);
		}
	}
}
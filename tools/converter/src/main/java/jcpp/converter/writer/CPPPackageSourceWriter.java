package jcpp.converter.writer;

import jcpp.converter.strategies.*;
import jcpp.converter.model.*;
import java.io.*;
import java.util.*;

public class CPPPackageSourceWriter{
	protected IStrategies strategies;
	protected CPPPackage pckge;

	public CPPPackageSourceWriter(IStrategies strategies,CPPPackage pckge){
		this.strategies=strategies;
		this.pckge=pckge;
	}

	public void write(File currentDir) throws Exception{
		File sourceFile=new File(currentDir,pckge.getSource().getCPPFileName());
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
		sb.append(System.lineSeparator());
		for (CPPType type : pckge.getSource().getIncludes()){
			sb.append("#include \"").append(type.getIncludePath()).append("\"").append(System.lineSeparator());
		}
		sb.append(System.lineSeparator());
	}

	protected void writeUsingNamespaces(StringBuffer sb){
		sb.append(System.lineSeparator());
		for (CPPType type : pckge.getSource().getUsings()){
			sb.append("using namespace ").append(type.getUsingNamespace()).append(";").append(System.lineSeparator());
		}
		sb.append(System.lineSeparator());
	}

	protected String writeStartNamespace(StringBuffer sb){
		String indnt="";
		for (String ns : pckge.getNamespaces()){
			sb.append(indnt+"namespace "+ns+"{").append(System.lineSeparator());
			indnt+="    ";
		}
		return indnt;
	}

	protected void writeBody(String ident,StringBuffer sb){
		sb.append(ident).append(pckge.getName()).append("::").append(pckge.getName()).append(":JPackage(new JString(\"").append(pckge.getJavaClassName()).append("\"),JPackage::getClazz()){").append(System.lineSeparator());
		for (CPPClass c : pckge.getClasses()){
			sb.append(ident).append("    addClass(").append(c.getName()).append("::getClazz());").append(System.lineSeparator());
		}
		sb.append(ident).append("}").append(System.lineSeparator()).append(System.lineSeparator());


		sb.append(ident).append("JPackage* ").append(pckge.getName()).append("::getSuperPackage(){").append(System.lineSeparator());
		if (pckge.getParent()!=null){
			sb.append(ident).append("    return ").append(pckge.getParent().getName()).append("::getPackage();").append(System.lineSeparator());
		}else{
			sb.append(ident).append("    return null;").append(System.lineSeparator());
		}
		sb.append(ident).append("}").append(System.lineSeparator()).append(System.lineSeparator());


		sb.append(ident).append("JList* ").append(pckge.getName()).append("::getPackages(){").append(System.lineSeparator());
		sb.append(ident).append("    if (packages->size()==0){").append(System.lineSeparator());
		for (CPPPackage sp : pckge.getSubPackages()){
			sb.append(ident).append("        addPackage(").append(sp.getName()).append("::getPackage());").append(System.lineSeparator());
		}
		sb.append(ident).append("    }").append(System.lineSeparator());
		sb.append(ident).append("    return packages;").append(System.lineSeparator());
		sb.append(ident).append("}").append(System.lineSeparator()).append(System.lineSeparator());

		sb.append(ident).append("static ").append(pckge.getName()).append("* pckge = null;").append(System.lineSeparator()).append(System.lineSeparator());

		sb.append(ident).append(pckge.getName()).append("* ").append(pckge.getName()).append("::getPackage(){").append(System.lineSeparator());
		sb.append(ident).append("    if (pckge==null){").append(System.lineSeparator());
		sb.append(ident).append("        pckge=new ").append(pckge.getName()).append("();").append(System.lineSeparator());
		sb.append(ident).append("    }").append(System.lineSeparator());
		sb.append(ident).append("    return pckge;").append(System.lineSeparator());		
		sb.append(ident).append("}").append(System.lineSeparator()).append(System.lineSeparator());

		sb.append(ident).append(pckge.getName()).append("::~").append(pckge.getName()).append("(){").append(System.lineSeparator());
		sb.append(ident).append("}").append(System.lineSeparator()).append(System.lineSeparator());
    }

	protected void writeEndNamespace(StringBuffer sb){
		for (int i=pckge.getNamespaces().size() ; i>0 ; i--){
			String indnt="";
			for (int j=0;j<i-1;j++){
				indnt+="    ";
			}
			sb.append(indnt+"}").append(System.lineSeparator());
		}
	}
}
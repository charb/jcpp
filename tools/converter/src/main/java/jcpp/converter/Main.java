package jcpp.converter;

import jcpp.converter.writer.*;
import jcpp.converter.model.*;
import jcpp.converter.strategies.*;
import jcpp.converter.builder.*;
import java.io.*;

public class Main{

	public static void main(String[] argv) throws Exception{
		IStrategies strategies=new DefaultStrategies();
		File byteDir=new File(argv[0]);
		File sourceDir=new File(argv[1]);
		CPPPackageBuilder builder=new CPPPackageBuilder(strategies);
		CPPPackage root=builder.build(byteDir,sourceDir);
		CPPWriter writer=new CPPWriter(strategies,root);
		writer.write(new File(argv[2]),new File(argv[3]));
	}
}
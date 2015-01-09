package jcpp.util.concurrent;

import java.io.*;
import org.junit.*;

public class AbstractTest{

	public AbstractTest(){
	}

	public static File createOutputFile(Class c) throws Exception{
		String outDir=System.getProperty("tests.outdir");
		File file=new File(outDir+'/'+c.getName().replace('.','/')+".ser");
		file.getParentFile().mkdirs();
		return file;
	}
}
package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class PrimitiveTest extends AbstractTest{
	private static ObjectOutputStream os;

	public PrimitiveTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(PrimitiveTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		boolean[] b=new boolean[2];
		b[0]=true;
		b[1]=false;

		byte[] by=new byte[2];
		by[0]=78;
		by[1]=79;

		char[] cs=new char[2];
		cs[0]='c';
		cs[1]='d';

		double[] ds=new double[2];
		ds[0]=78;
		ds[1]=79;

		float[] fs=new float[2];
		fs[0]=78;
		fs[1]=79;

		int[] is=new int[2];
		is[0]=78;
		is[1]=79;

		long[] ls=new long[2];
		ls[0]=78;
		ls[1]=79;

		short[] ss=new short[2];
		ss[0]=78;
		ss[1]=79;

		Object[] oos=new Object[8];
		oos[0]=b;
		oos[1]=by;
		oos[2]=cs;
		oos[3]=ds;
		oos[4]=fs;
		oos[5]=is;
		oos[6]=ls;
		oos[7]=ss;

		os.writeObject(oos);
	}
}
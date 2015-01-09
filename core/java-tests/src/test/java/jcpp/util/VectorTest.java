package jcpp.util;

import jcpp.*;
import java.io.*;
import java.util.*;
import org.junit.*;

public class VectorTest extends AbstractTest{
	private static ObjectOutputStream os;

	public VectorTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(VectorTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		Vector a1=new Vector();
		a1.add(new SampleObject());
		a1.add(new Integer(0));
		a1.add(new SampleObject());
		a1.add(new Vector());
		a1.add("index4");
		a1.add("index5");
		a1.add(new Float(78));
		a1.add(new Short((short)78));
		a1.add(new Vector());
		a1.add(new Long(78));
		os.writeObject(a1);	
	}
}
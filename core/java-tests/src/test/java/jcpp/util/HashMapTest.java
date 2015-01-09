package jcpp.util;

import jcpp.*;
import java.io.*;
import java.util.*;
import org.junit.*;

public class HashMapTest extends AbstractTest{
	private static ObjectOutputStream os;

	public HashMapTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(HashMapTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		HashMap a1=new HashMap();
		a1.put("index0",new SampleObject());
		a1.put("index1",new Integer(0));
		a1.put("index2",new SampleObject());
		a1.put("index3",new HashMap());
		a1.put("index4","index4");
		a1.put("index5","index5");
		a1.put("index6",new Float(78));
		a1.put("index7",new Short((short)78));
		a1.put("index8",new ArrayList());
		a1.put("index9",new Long(78));
		a1.put("index10",new HashMap());
		os.writeObject(a1);	
	}
}
package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class IntegerTest extends AbstractTest{
	private static ObjectOutputStream os;

	public IntegerTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(IntegerTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		os.writeObject(new Integer[]{new Integer((int)78),new Integer((int)Integer.MAX_VALUE),new Integer((int)Integer.MIN_VALUE)});	
	}
}
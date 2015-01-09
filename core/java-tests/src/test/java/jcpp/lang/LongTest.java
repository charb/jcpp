package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class LongTest extends AbstractTest{
	private static ObjectOutputStream os;

	public LongTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(LongTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		os.writeObject(new Long[]{new Long((long)78),new Long((long)Long.MAX_VALUE),new Long((long)Long.MIN_VALUE)});	
	}
}
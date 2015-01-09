package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class StringBufferTest extends AbstractTest{
	private static ObjectOutputStream os;

	public StringBufferTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(StringBufferTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		StringBuffer b=new StringBuffer();
		b.append("This is a test");
		os.writeObject(b);	
	}
}
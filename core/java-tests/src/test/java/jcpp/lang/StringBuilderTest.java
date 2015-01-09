package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class StringBuilderTest extends AbstractTest{
	private static ObjectOutputStream os;

	public StringBuilderTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(StringBuilderTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		StringBuilder b=new StringBuilder();
		b.append("This is a test");
		os.writeObject(b);	
	}
}
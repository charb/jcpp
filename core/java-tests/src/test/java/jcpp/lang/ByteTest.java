package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class ByteTest extends AbstractTest{
	private static ObjectOutputStream os;

	public ByteTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(ByteTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		os.writeObject(new Byte[]{new Byte((byte)78),new Byte(Byte.MAX_VALUE),new Byte(Byte.MIN_VALUE)});	
	}
}
package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class FloatTest extends AbstractTest{
	private static ObjectOutputStream os;

	public FloatTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(FloatTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		os.writeObject(new Float[]{new Float((float)78),new Float((float)Float.MAX_VALUE),new Float((float)Float.MIN_VALUE)});	
	}
}
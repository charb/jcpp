package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class DoubleTest extends AbstractTest{
	private static ObjectOutputStream os;

	public DoubleTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(DoubleTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		os.writeObject(new Double[]{new Double((double)78),new Double((double)Double.MAX_VALUE),new Double((double)Double.MIN_VALUE)});	
	}
}
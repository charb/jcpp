package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class BooleanTest extends AbstractTest{
	private static ObjectOutputStream os;

	public BooleanTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(BooleanTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		os.writeObject(new Boolean(true));	
	}
}
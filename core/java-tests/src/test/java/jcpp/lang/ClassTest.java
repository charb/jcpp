package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class ClassTest extends AbstractTest{
	private static ObjectOutputStream os;

	public ClassTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(ClassTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		os.writeObject(Object.class);	
	}
}
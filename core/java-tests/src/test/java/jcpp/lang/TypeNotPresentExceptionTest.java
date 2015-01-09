package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class TypeNotPresentExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public TypeNotPresentExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(TypeNotPresentExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		Exception cause=new Exception("This is the cause");
		TypeNotPresentException exception=new TypeNotPresentException("TYPE_NAME",cause);
		os.writeObject(exception);	
	}
}
package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class EnumConstantNotPresentExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public EnumConstantNotPresentExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(EnumConstantNotPresentExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		EnumConstantNotPresentException exception=new EnumConstantNotPresentException(EnumSampleObject.class,"ENUM6");
		os.writeObject(exception);	
	}
}
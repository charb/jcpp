package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class ClassCircularityErrorTest extends AbstractTest{
	private static ObjectOutputStream os;

	public ClassCircularityErrorTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(ClassCircularityErrorTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		ClassCircularityError cause=new ClassCircularityError("This is the cause");
		ClassCircularityError exception=new ClassCircularityError("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}
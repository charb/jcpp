package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class EnumSampleObjectTest extends AbstractTest{
	private static ObjectOutputStream os;

	public EnumSampleObjectTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(EnumSampleObjectTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		EnumSampleObject[] e=new EnumSampleObject[5];
		e[0]=EnumSampleObject.ENUM5;
		e[1]=EnumSampleObject.ENUM4;
		e[2]=EnumSampleObject.ENUM3;
		e[3]=EnumSampleObject.ENUM2;
		e[4]=EnumSampleObject.ENUM1;
		os.writeObject(e);	
	}
}
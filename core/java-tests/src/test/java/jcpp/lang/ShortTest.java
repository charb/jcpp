package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class ShortTest extends AbstractTest{
	private static ObjectOutputStream os;

	public ShortTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(ShortTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		os.writeObject(new Short[]{new Short((short)78),new Short((short)Short.MAX_VALUE),new Short((short)Short.MIN_VALUE)});
	}
}
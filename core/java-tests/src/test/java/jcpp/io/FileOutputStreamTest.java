package jcpp.io;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class FileOutputStreamTest extends AbstractTest{
	private static FileOutputStream os;

	public FileOutputStreamTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(FileOutputStreamTest.class);
		os=new FileOutputStream(file);
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		os.write(0);
		os.write(1);
		os.write(2);
		os.write(3);
		os.write(4);
		os.write(5);
		os.write(6);
		os.write(7);
		os.write(8);
		os.write(9);
		os.write(10);
		byte[] b=new byte[]{0,1,2,3,4,5,6,7,8,9,10};
		os.write(b);
	}
}
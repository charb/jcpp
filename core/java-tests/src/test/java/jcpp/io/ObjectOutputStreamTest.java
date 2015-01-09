package jcpp.io;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class ObjectOutputStreamTest extends AbstractTest{
	private static ObjectOutputStream os;

	public ObjectOutputStreamTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(ObjectOutputStreamTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
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

		os.writeBoolean(true);
		os.writeBoolean(false);

		os.writeBytes("Hello world");

		os.writeChar('T');
		os.writeChar('E');
		os.writeChar('S');
		os.writeChar('T');

		os.writeChars("Hello world");

		os.writeDouble(1978);

		os.writeFloat(1978);

		os.writeInt(1978);

		os.writeLong(1978);

		os.writeShort(1978);

		os.writeUTF("Hello world");

		SampleObject so=new SampleObject(0,(long)1,(short)2,(float)3,(double)4,true,'T',(byte)5);
		os.writeObject(so);	
	}
}
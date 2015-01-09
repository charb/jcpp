package jcpp.util.concurrent.atomic;

import jcpp.util.concurrent.*;
import java.io.*;
import java.util.concurrent.atomic.*;
import org.junit.*;

public class AtomicBooleanTest extends AbstractTest{
	private static ObjectOutputStream os;

	public AtomicBooleanTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(AtomicBooleanTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		AtomicBoolean a1=new AtomicBoolean(true);
		os.writeObject(a1);	
	}
}
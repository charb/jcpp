package jcpp.net;

import jcpp.*;
import java.io.*;
import java.net.*;
import org.junit.*;

public class SocketExceptionTest extends AbstractTest {

	private static ObjectOutputStream os;

	public SocketExceptionTest() {
	}

	@BeforeClass
	public static void setUp() throws Exception {
		File file = createOutputFile(SocketExceptionTest.class);
		os = new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception {
		os.close();
	}

	@Test
	public void testWrite() throws Exception {
		SocketException cause = new SocketException("This is the cause");
		SocketException exception = new SocketException("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);
	}
}

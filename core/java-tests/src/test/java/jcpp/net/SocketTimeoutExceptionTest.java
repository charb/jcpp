package jcpp.net;

import jcpp.*;
import java.io.*;
import java.net.*;
import org.junit.*;

public class SocketTimeoutExceptionTest extends AbstractTest {

	private static ObjectOutputStream os;

	public SocketTimeoutExceptionTest() {
	}

	@BeforeClass
	public static void setUp() throws Exception {
		File file = createOutputFile(SocketTimeoutExceptionTest.class);
		os = new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception {
		os.close();
	}

	@Test
	public void testWrite() throws Exception {
		SocketTimeoutException cause = new SocketTimeoutException("This is the cause");
		SocketTimeoutException exception = new SocketTimeoutException("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);
	}
}

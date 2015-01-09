package jcpp.nio;

import java.io.File;
import java.io.FileOutputStream;
import java.io.OutputStreamWriter;
import java.io.Writer;

import org.junit.AfterClass;
import org.junit.BeforeClass;
import org.junit.Test;

public class StringEncodingTest {

	private static final String UTF8_TEST_STRING = "the quick brown fox jumps over the lazy dog THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG\t\n,.;:!?[](){}!1234567890!@#$%^&*~-";
	
	private static String UTF8_ENCODING = "UTF-8";


	public StringEncodingTest() {
	}

	public static File createOutputFile(String encoding) throws Exception {
		String outDir = System.getProperty("tests.outdir");
		File file = new File(outDir + '/' + StringEncodingTest.class.getName().replace('.', '/') + "_" + encoding + ".strEncoding");
		file.getParentFile().mkdirs();
		return file;
	}

	@Test
	public void testUtf8Encoding() throws Exception {
		FileOutputStream stream = new FileOutputStream(createOutputFile(UTF8_ENCODING));
		try {
			byte[] bytes = UTF8_TEST_STRING.getBytes(UTF8_ENCODING);
			stream.write(bytes);
		} finally {
			try {
				stream.close();
			} catch (Exception e) {
			}
		}
	}

}

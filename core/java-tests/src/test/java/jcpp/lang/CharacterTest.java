package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class CharacterTest extends AbstractTest{
	private static ObjectOutputStream os;

	public CharacterTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(CharacterTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		os.writeObject(new Character[]{new Character('c'),new Character(Character.MAX_VALUE),new Character(Character.MIN_VALUE)});			
	}
}
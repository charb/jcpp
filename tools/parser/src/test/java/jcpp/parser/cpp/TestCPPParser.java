package jcpp.parser.cpp;

import java.io.InputStream;
import java.net.URL;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;

import org.junit.Assert;
import org.junit.Test;


public class TestCPPParser {

    public TestCPPParser() {
    }


    @Test
    public void testSample1() throws Exception {
        List<String> fileNames = Arrays.asList("/Sample1.h", "/Sample1.cpp");

        for (String fileName : fileNames) {
            CPPFile cppFileParsed = parseFile(fileName);
            CPPFile cppFileExpected = readFile(fileName + ".xml");
            if ((cppFileExpected == null) || !cppFileParsed.equals(cppFileExpected)) {
                cppFileParsed.writeTo(System.out);
            }
            Assert.assertEquals("Comparing file " + fileName, cppFileExpected, cppFileParsed);
        }
    }

    protected CPPFile parseFile(String strFile) throws Exception {
        CPPParser parser = new CPPParser();
        parser.setIncludes(new ArrayList<String>());
        parser.setSymbols(new HashMap<String, String>());
        URL resourceUrl = this.getClass().getResource(strFile);
        Path resourcePath = Paths.get(resourceUrl.toURI());
        parser.parse(resourcePath.toFile());
        return parser.getCPPFiles()[0];
    }

    protected CPPFile readFile(String strFile) throws Exception {
        InputStream in = this.getClass().getResourceAsStream(strFile);
        if (in != null) {
            return CPPFile.readFrom(in);
        } else {
            return null;
        }
    }
}

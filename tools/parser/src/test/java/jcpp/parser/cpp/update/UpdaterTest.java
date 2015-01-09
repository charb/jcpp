package jcpp.parser.cpp.update;

import java.io.InputStream;

import java.net.URL;

import java.nio.file.Path;
import java.nio.file.Paths;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;

import jcpp.parser.cpp.CPPClass;
import jcpp.parser.cpp.CPPField;
import jcpp.parser.cpp.CPPFile;
import jcpp.parser.cpp.CPPMethod;
import jcpp.parser.cpp.CPPMethodParameter;
import jcpp.parser.cpp.CPPNamespace;
import jcpp.parser.cpp.CPPParser;
import jcpp.parser.cpp.CPPVariable;

import org.junit.Assert;
import org.junit.Test;


public class UpdaterTest {

    public UpdaterTest() {
    }


    @Test
    public void testIntrumentationUpdater() throws Exception {
        Updater updater = new Updater();
        updater.addVariableCodeGenerator(new VariableCodeGenerator(), Collections.singletonList("variableInjection.h"));
        updater.addMethodCodeGenerator(new MethodCodeGenerator(), Collections.singletonList("methodInjection.h"));
        updater.addFieldCodeGenerator(new FieldCodeGenerator(), Collections.singletonList("fieldInjection.h"));
        updater.addMemberInitializerCodeGenerator(new MemberInitializerGenerator(), Collections.singletonList("memberInitializer.h"));
        updater.addEndOfNamespaceCodeGenerator(new NamespaceCodeGenerator(), Collections.singletonList("namespaceInjection.h"));
        updater.addClassCodeGenerator(new ClassCodeGenerator(), Collections.singletonList("classInjection.h"));
        updater.addForStatementInitializerVariableCodeGenerator(new ForInitializerCodeGenerator(), Collections.<String>emptyList());

        List<String> filenames = Arrays.asList("/Sample1.h", "/Sample1.cpp");
        for (String filename : filenames) {
            CPPFile cppFile = parseFile(filename);
            updater.insertEndOfFileIncludes(Collections.singletonList("endOfFile.h"));
            UpdatesResult updatesResult = updater.update(cppFile);
            String updatedContent = updatesResult.getContent();
            System.out.println(updatedContent);
            String expectedContent = readFileContent(filename + ".instrumented");
            Assert.assertEquals(expectedContent, updatedContent);
            updater.clear();
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

    protected String readFileContent(String strFile) throws Exception {
        InputStream is = this.getClass().getResourceAsStream(strFile);
        try {
            StringBuffer sb = new StringBuffer();
            byte[] buffer = new byte[4096];
            int read = 0;
            while ((read = is.read(buffer, 0, 4096)) > -1) {
                sb.append(new String(buffer, 0, read));
            }
            return sb.toString();
        } finally {
            is.close();
        }
    }


    private static class VariableCodeGenerator implements ICodeGenerator<CPPVariable> {

        public VariableCodeGenerator() {
        }


        @Override
        public String generate(CPPVariable construct) {
            return "DeclaredVariable(" + construct.getName() + ");";
        }

    }

    private static class NamespaceCodeGenerator implements ICodeGenerator<CPPNamespace> {

        public NamespaceCodeGenerator() {
        }


        @Override
        public String generate(CPPNamespace construct) {
            return "/*DeclaredNamespace(" + construct.getLastName() + ");*/";
        }

    }

    private static class ClassCodeGenerator implements ICodeGenerator<CPPClass> {

        public ClassCodeGenerator() {
        }


        @Override
        public String generate(CPPClass construct) {
            return "/*DeclaredClass(" + construct.getSimpleName() + ");*/";
        }

    }

    private static class MethodCodeGenerator implements ICodeGenerator<CPPMethod> {

        public MethodCodeGenerator() {
        }


        @Override
        public String generate(CPPMethod construct) {
            StringBuilder sb = new StringBuilder("/*DeclaredMethod(").append(construct.getName()).append(");*/").append(System.lineSeparator());
            for (CPPMethodParameter parameter : construct.getParameters()) {
                sb.append("DeclaredParameter(").append(parameter.getName()).append(");").append(System.lineSeparator());
            }
            return sb.toString();
        }
    }

    private static class FieldCodeGenerator implements ICodeGenerator<CPPField> {

        public FieldCodeGenerator() {
        }


        @Override
        public String generate(CPPField construct) {
            return "/*DeclaredField(" + construct.getName() + ");*/";
        }

    }

    private static class MemberInitializerGenerator implements ICodeGenerator<CPPMethod> {

        public MemberInitializerGenerator() {
        }


        @Override
        public String generate(CPPMethod construct) {
            return "__objectInfo()";
        }

    }

    private static class ForInitializerCodeGenerator implements IEnhancedCodeGenerator<CPPVariable> {

        public ForInitializerCodeGenerator() {
        }


        @Override
        public String generateBefore(CPPVariable construct) {
            return "/*before for: " + construct.getName() + "*/";
        }

        @Override
        public String generate(CPPVariable construct) {
            return construct.getDeclaration().getRawSignature();
        }

        @Override
        public String generateAfter(CPPVariable construct) {
            return "/*after for: " + construct.getName() + "*/";
        }
    }

}

package jcpp.mavenplugin.code.reflect;

import jcpp.parser.cpp.CPPClass;
import jcpp.parser.cpp.CPPFile;
import jcpp.parser.cpp.CPPNamespace;
import jcpp.parser.cpp.update.CodeGeneratorContext;
import jcpp.parser.cpp.update.ICodeGenerator;


public class ReflectionStartOfNamespaceCodeGenerator implements ICodeGenerator<CPPNamespace> {

    private CPPFile cppFile;


    public ReflectionStartOfNamespaceCodeGenerator(CPPFile cppFile) {
        this.cppFile = cppFile;
    }


    @Override
    public String generate(CPPNamespace construct, CodeGeneratorContext context) {
        StringBuilder sb = new StringBuilder();

        if (cppFile != null) {
            for (CPPClass cppClass : cppFile.getClasses()) {
                if (cppClass.getCompositeTypeSpecifier() != null) {
                    if (construct.getName().equals(cppClass.getNamespaceName())) {
                        sb.append("\nclass ").append(cppClass.getSimpleName()).append("Class;\n");
                    }
                }
            }

        }

        return sb.toString();
    }

}

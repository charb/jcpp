package jcpp.mavenplugin.code.reflect;

import jcpp.mavenplugin.code.Utils;

import jcpp.parser.cpp.CPPClass;
import jcpp.parser.cpp.CPPFile;
import jcpp.parser.cpp.update.ICodeGenerator;


public class ReflectionClassCodeGenerator implements ICodeGenerator<CPPClass> {

    private CPPFile cppFile;


    public ReflectionClassCodeGenerator(CPPFile cppFile) {
        this.cppFile = cppFile;
    }


    @Override
    public String generate(CPPClass construct) {
        StringBuilder sb = new StringBuilder();
        if (construct.getCompositeTypeSpecifier() != null) {
            sb.append("\nfriend class ").append(construct.getSimpleName()).append("Class;\n");

            for (CPPClass classDeclaration : cppFile.getClasses()) {
                String declaredParentClassName = Utils.getDeclaredParentClassName(classDeclaration);
                if ((declaredParentClassName != null) && declaredParentClassName.equals(construct.getSimpleName())) {
                    sb.append("\nfriend class ").append(classDeclaration.getSimpleName()).append("Class;\n");
                }
            }

        }
        return sb.toString();
    }

}

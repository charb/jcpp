package jcpp.mavenplugin.code.gc;

import jcpp.parser.cpp.CPPType;
import jcpp.parser.cpp.CPPVariable;
import jcpp.parser.cpp.update.CodeGeneratorContext;
import jcpp.parser.cpp.update.IEnhancedCodeGenerator;


public class GcForLoopVariableCodeGenerator implements IEnhancedCodeGenerator<CPPVariable> {
    private static GcForLoopVariableCodeGenerator instance;


    private GcForLoopVariableCodeGenerator() {
    }


    public static synchronized GcForLoopVariableCodeGenerator getInstance() {
        if (instance == null) {
            instance = new GcForLoopVariableCodeGenerator();
        }
        return instance;
    }

    @Override
    public String generate(CPPVariable construct, CodeGeneratorContext context) {
        return construct.getType().isPointer() ? " ;" : null;
    }

    @Override
    public String generateBefore(CPPVariable construct, CodeGeneratorContext context) {
        StringBuilder sb = new StringBuilder();

        CPPType cppType = construct.getType();
        if (cppType.isPointer()) {
            String variableName = construct.getName();

            sb.append("\n{");
            sb.append("\n").append(context.getSourceContext(construct.getDeclaration()));
            sb.append("\n VariableInfo __").append(variableName).append("VariableInfo(&__methodCallInfo, (void**)&").append(variableName).append(");\n");
        }

        return sb.toString();
    }

    @Override
    public String generateAfter(CPPVariable construct, CodeGeneratorContext context) {
        StringBuilder sb = new StringBuilder();

        CPPType cppType = construct.getType();
        if (cppType.isPointer()) {
            sb.append("\n}\n");
        }

        return sb.toString();
    }

}

package jcpp.mavenplugin.code.gc;

import jcpp.parser.cpp.CPPField;
import jcpp.parser.cpp.CPPType;
import jcpp.parser.cpp.update.CodeGeneratorContext;
import jcpp.parser.cpp.update.ICodeGenerator;


public class GcFieldCodeGenerator implements ICodeGenerator<CPPField> {

    private static GcFieldCodeGenerator instance;


    private GcFieldCodeGenerator() {
    }


    public static synchronized GcFieldCodeGenerator getInstance() {
        if (instance == null) {
            instance = new GcFieldCodeGenerator();
        }
        return instance;
    }

    @Override
    public String generate(CPPField construct, CodeGeneratorContext context) {
        StringBuilder sb = new StringBuilder();

        CPPType type = construct.getType();
        if (type.isPointer()) {
            if (type.isStatic()) {
                sb.append("\nstatic FieldInfo __").append(construct.getName()).append("StaticFieldInfo;\n");
            } else if((construct.getCppClass() != null) && (GcClassCodeGenerator.isObject(construct.getCppClass()))) {
                sb.append("\nFieldInfo __").append(construct.getName()).append("FieldInfo;\n");
            }
        }
        return sb.toString();
    }

}

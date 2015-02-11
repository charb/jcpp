package jcpp.mavenplugin.code.gc;

import jcpp.parser.cpp.CPPField;
import jcpp.parser.cpp.CPPType;
import jcpp.parser.cpp.update.CodeGeneratorContext;
import jcpp.parser.cpp.update.ICodeGenerator;


public class GcFieldCodeGenerator implements ICodeGenerator<CPPField> {

	private final GcFileTupleContext gcContext;

    public GcFieldCodeGenerator(GcFileTupleContext gcContext) {
    	this.gcContext = gcContext;
    }


    @Override
    public String generate(CPPField construct, CodeGeneratorContext context) {
        CPPType type = construct.getType();
        if (type.isPointer()) {
            StringBuilder sb = new StringBuilder();
            if (type.isStatic()) {
                sb.append("\nstatic FieldInfo __").append(construct.getName()).append("StaticFieldInfo;\n");
            } else if((construct.getCppClass() != null) && gcContext.getClassContext(construct.getCppClass().getName()).isObject()) {
            	sb.append("\nstatic NativeString __").append(construct.getName()).append("FieldName;");
                sb.append("\nFieldInfo __").append(construct.getName()).append("FieldInfo;\n");
            }
            return sb.toString();
        }
        return null;
    }

}

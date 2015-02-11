package jcpp.mavenplugin.code.gc;

import jcpp.parser.cpp.CPPType;
import jcpp.parser.cpp.CPPVariable;
import jcpp.parser.cpp.update.CodeGeneratorContext;
import jcpp.parser.cpp.update.ICodeGenerator;

import org.eclipse.cdt.core.dom.ast.IASTNode;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPASTCatchHandler;


// TODO : Update for static variables
public class GcVariableCodeGenerator implements ICodeGenerator<CPPVariable> {
	private final GcFileTupleContext gcContext;

    public GcVariableCodeGenerator(GcFileTupleContext gcContext) {
    	this.gcContext = gcContext;
    }

    public static boolean isVariableInCatchBlock(CPPVariable cppVariable) {
        IASTNode node = cppVariable.getDeclaration();
        while (node != null) {
            if (node instanceof ICPPASTCatchHandler) {
                return true;
            }
            node = node.getParent();
        }
        return false;
    }

    @Override
    public String generate(CPPVariable construct, CodeGeneratorContext context) {
        StringBuilder sb = new StringBuilder();

        CPPType cppType = construct.getType();
        if (cppType.isPointer()) {
            if (!isVariableInCatchBlock(construct)) {
                if (!cppType.isStatic()) {
                    String variableName = construct.getName();
                    sb.append("\nVariableInfo __").append(variableName).append("VariableInfo(&__methodCallInfo, (void**)&").append(variableName).append(", ").append(gcContext.getCurrentVariableIndex(construct)).append(");\n");
                }
            }
        }

        return sb.toString();
    }

}

package jcpp.mavenplugin.code.gc;

import java.util.List;

import jcpp.parser.cpp.CPPClass;
import jcpp.parser.cpp.CPPField;
import jcpp.parser.cpp.CPPFile;
import jcpp.parser.cpp.CPPMethod;
import jcpp.parser.cpp.CPPMethodParameter;
import jcpp.parser.cpp.CPPVariable;
import jcpp.parser.cpp.update.CodeGeneratorContext;
import jcpp.parser.cpp.update.ICodeGenerator;


public class GcMethodCodeGenerator implements ICodeGenerator<CPPMethod> {

	private final GcFileTupleContext gcContext;


    public GcMethodCodeGenerator(GcFileTupleContext gcContext) {
    	this.gcContext = gcContext;
    }


    @Override
    public String generate(CPPMethod construct, CodeGeneratorContext context) {
        StringBuilder sb = new StringBuilder();

        CPPClass cppClass = null;
        CPPFile headerCppFile = gcContext.isHeaderUpdater() ? null : gcContext.getHeaderCPPFile();
        if ((construct.getCppClass() != null) && (headerCppFile != null)) {
            cppClass = headerCppFile.getClass(construct.getCppClass().getName());
        }
        if (cppClass == null) {
            cppClass = construct.getCppClass();
        }
        
        GcClassContext classContext = cppClass == null ? null : gcContext.getClassContext(cppClass.getName());
        
        if ((cppClass != null) && (classContext != null) && classContext.isObject() && construct.isConstructor()) {
            List<CPPField> fields = cppClass.getFields();
            int count = 0;
            for (int fieldIndex = 0; fieldIndex < fields.size(); fieldIndex++) {
            	CPPField field = fields.get(fieldIndex);
                if (field.getType().isPointer() && !field.getType().isStatic()) {
                    String fieldName = field.getName();
                    sb.append("\n__objectInfo.addFieldInfo(").append(count++).append(", &__").append(fieldName).append("FieldInfo);");
                }
            }
        }

        int parameterCount = 0;
        List<CPPMethodParameter> parameters = construct.getParameters();
        for(CPPMethodParameter parameter : parameters) {
        	if (parameter.getType().isPointer()) {
        		parameterCount++;
        	}
        }
        if(parameterCount > 0) {
        	sb.append("\nParameterInfo* __parameterInfos[").append(parameterCount).append("];");
        }
        
        int variableCount = 0;
        List<CPPVariable> variables = construct.getVariables();
        for(CPPVariable variable : variables) {
        	if (variable.getType().isPointer()) {
        		variableCount++;
        	}
        }
        if(variableCount > 0) {
        	sb.append("\nVariableInfo* __variableInfos[").append(variableCount).append("];");
        }
        
        String methodName = construct.getName();
        sb.append("\nMethodCallInfo __methodCallInfo(");
        if(classContext != null && classContext.getNonPureVirtualMethodNames().contains(methodName)) {
        	sb.append("&__");
        	if(methodName.startsWith("~")) {
        		sb.append("destructor").append(methodName.substring(1));
        	} else {
        		sb.append(methodName);
        	}
        	sb.append("MethodName");
        } else {
        	sb.append("null");
        }
        
        if((cppClass != null) && (classContext != null) && classContext.isObject() && !construct.getFunction().isStatic()) {
            sb.append(", &__objectInfo, ");
        } else {
        	sb.append(", null, ");
        }
        sb.append(parameterCount).append(", ").append(parameterCount > 0 ? "__parameterInfos, ": "null, ");
        sb.append(variableCount).append(", ").append(variableCount > 0 ? "__variableInfos": "null");
        sb.append(");\n");

        int parameterIndex = 0;
        for (int index = 0; index < parameters.size(); index++) {
        	CPPMethodParameter parameter = parameters.get(index);
            if (parameter.getType().isPointer()) {
                String parameterName = parameter.getName();
                sb.append("ParameterInfo __").append(parameterName).append("ParameterInfo(&__methodCallInfo, (void**)&").append(parameterName).append(", ").append(parameterIndex++).append(");\n");
            }
        }
        return sb.toString();
    }

}

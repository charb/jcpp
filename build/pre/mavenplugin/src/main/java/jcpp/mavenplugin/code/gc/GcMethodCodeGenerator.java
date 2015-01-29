package jcpp.mavenplugin.code.gc;

import java.util.List;

import jcpp.parser.cpp.CPPClass;
import jcpp.parser.cpp.CPPField;
import jcpp.parser.cpp.CPPFile;
import jcpp.parser.cpp.CPPMethod;
import jcpp.parser.cpp.CPPMethodParameter;
import jcpp.parser.cpp.CPPType;
import jcpp.parser.cpp.update.ICodeGenerator;


public class GcMethodCodeGenerator implements ICodeGenerator<CPPMethod> {

    private final CPPFile headerCppFile;


    public GcMethodCodeGenerator(CPPFile headerCppFile) {
        this.headerCppFile = headerCppFile;
    }


    @Override
    public String generate(CPPMethod construct) {
        StringBuilder sb = new StringBuilder();

        CPPClass cppClass = null;
        if ((construct.getCppClass() != null) && (headerCppFile != null)) {
            cppClass = headerCppFile.getClass(construct.getCppClass().getName());
        }
        if (cppClass == null) {
            cppClass = construct.getCppClass();
        }
        
        if ((cppClass != null) && GcClassCodeGenerator.isObject(cppClass) && construct.isConstructor()) {
            if (cppClass != null) {
                List<CPPField> fields = cppClass.getFields();
                for (CPPField field : fields) {
                    CPPType type = field.getType();
                    if (type.isPointer()) {
                        if (!type.isStatic()) {
                            String fieldName = field.getName();
                            sb.append("\n__objectInfo.addFieldInfo(&__").append(fieldName).append("FieldInfo);");
                        }
                    }
                }
            }
        }

        if ((cppClass == null) || construct.getFunction().isStatic()) {
            sb.append("\nMethodCallInfo __methodCallInfo(\"").append(construct.getName()).append("\", NULL);\n");
        } else if((cppClass != null) && GcClassCodeGenerator.isObject(cppClass)) {
            sb.append("\nMethodCallInfo __methodCallInfo(\"").append(construct.getName()).append("\", &__objectInfo);\n");
        }

        List<CPPMethodParameter> parameters = construct.getParameters();
        for (CPPMethodParameter parameter : parameters) {
            CPPType type = parameter.getType();
            if (type.isPointer()) {
                String parameterName = parameter.getName();
                sb.append("ParameterInfo __").append(parameterName).append("ParameterInfo(&__methodCallInfo, \"").append(parameterName).append("\", (void**)&").append(parameterName).append(");\n");
            }
        }
        return sb.toString();
    }

}

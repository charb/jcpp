package jcpp.mavenplugin.code.gc;

import java.util.List;

import jcpp.parser.cpp.CPPClass;
import jcpp.parser.cpp.CPPField;
import jcpp.parser.cpp.CPPFile;
import jcpp.parser.cpp.CPPMethod;
import jcpp.parser.cpp.CPPType;
import jcpp.parser.cpp.update.CodeGeneratorContext;
import jcpp.parser.cpp.update.ICodeGenerator;


public class GcMemberInitializerCodeGenerator implements ICodeGenerator<CPPMethod> {

    private final CPPFile headerCppFile;


    public GcMemberInitializerCodeGenerator(CPPFile headerCppFile) {
        this.headerCppFile = headerCppFile;
    }


    @Override
    public String generate(CPPMethod construct, CodeGeneratorContext context) {
        StringBuilder sb = new StringBuilder();

        sb.append("__objectInfo(&__classInfo, this)");

        String className = construct.getCppClass().getName();
        CPPClass cppClass = null;

        if (headerCppFile != null) {
            cppClass = headerCppFile.getClass(className);
        }
        if (cppClass == null) {
            cppClass = construct.getCppClass();
        }

        if ((cppClass != null) && GcClassCodeGenerator.isObject(cppClass)) {
            List<CPPField> fields = cppClass.getFields();
            for (CPPField field : fields) {
                CPPType type = field.getType();
                if (type.isPointer()) {
                    if (!type.isStatic()) {
                        String fieldName = field.getName();
                        sb.append(", __").append(fieldName).append("FieldInfo(\"").append(fieldName).append("\", (void**)&").append(fieldName).append(")");
                    }
                }
            }
        }

        return sb.toString();
    }

}

package jcpp.mavenplugin.code.gc;

import java.util.HashSet;
import java.util.List;
import java.util.Set;

import jcpp.parser.cpp.CPPClass;
import jcpp.parser.cpp.CPPField;
import jcpp.parser.cpp.CPPFile;
import jcpp.parser.cpp.CPPNamespace;
import jcpp.parser.cpp.CPPType;
import jcpp.parser.cpp.update.CodeGeneratorContext;
import jcpp.parser.cpp.update.ICodeGenerator;


public class GcEndOfNamespaceCodeGenerator implements ICodeGenerator<CPPNamespace> {

    private final CPPFile headerCppFile;
    private final CPPFile cppCppFile;
    private final Set<String> namespacesUpdated;
    private final Set<String> classNamesWritten;


    public GcEndOfNamespaceCodeGenerator(CPPFile headerCppFile, CPPFile cppCppFile) {
        this.headerCppFile = headerCppFile;
        this.cppCppFile = cppCppFile;
        namespacesUpdated = new HashSet<String>();
        classNamesWritten = new HashSet<String>();
    }


    @Override
    public String generate(CPPNamespace construct, CodeGeneratorContext context) {
        StringBuilder sb = new StringBuilder();

        String namespace = construct.getName();
        if (!namespacesUpdated.contains(namespace)) {
            namespacesUpdated.add(namespace);

            if (headerCppFile != null) {
                generateCodeForCppClasses(sb, namespace, headerCppFile.getClasses());
            }

            if (cppCppFile != null) {
                generateCodeForCppClasses(sb, namespace, cppCppFile.getClasses());
            }

        }

        return sb.toString();
    }

    private void generateCodeForCppClasses(StringBuilder sb, String namespace, CPPClass[] classes) {
        if (classes != null) {
            for (CPPClass cppClass : classes) {
                String classNamespaceName = cppClass.getNamespaceName();
                if (classNamespaceName.equals(namespace)) {
                    String className = cppClass.getName();

                    if (!classNamesWritten.contains(className)) {
                        classNamesWritten.add(className);

                        sb.append("\nClassInfo ").append(className).append("::__classInfo(\"").append(classNamespaceName).append("\", \"").append(className).append("\");\n");
                        List<CPPField> fields = cppClass.getFields();
                        for (CPPField field : fields) {
                            CPPType type = field.getType();
                            if (type.isPointer()) {
                                if (type.isStatic()) {
                                    String fieldName = field.getName();
                                    sb.append("FieldInfo ").append(className).append("::__").append(fieldName).append("StaticFieldInfo(&__classInfo, \"").append(fieldName).append("\", (void**)&").append(fieldName).append(");\n");
                                }
                            }
                        }
                    }
                }
            }
        }
    }

}

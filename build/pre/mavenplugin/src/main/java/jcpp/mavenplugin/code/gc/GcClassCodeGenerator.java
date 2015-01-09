package jcpp.mavenplugin.code.gc;

import java.util.LinkedList;

import jcpp.parser.cpp.CPPBaseClass;
import jcpp.parser.cpp.CPPClass;
import jcpp.parser.cpp.update.ICodeGenerator;


public class GcClassCodeGenerator implements ICodeGenerator<CPPClass> {

    private static final String J_OBJECT_CLASS_NAME = "JObject";
    private static GcClassCodeGenerator instance;


    private GcClassCodeGenerator() {
    }


    public static synchronized GcClassCodeGenerator getInstance() {
        if (instance == null) {
            instance = new GcClassCodeGenerator();
        }
        return instance;
    }

    public static boolean isObject(CPPClass cppClass) {
        String simpleName = cppClass.getSimpleName();
        if (simpleName.equals(J_OBJECT_CLASS_NAME)) {
            return true;
        }

        LinkedList<CPPBaseClass> stack = new LinkedList<CPPBaseClass>();

        stack.addAll(cppClass.getBaseClasses());
        while (stack.size() > 0) {
            CPPBaseClass baseClass = stack.pop();
            stack.addAll(baseClass.getBaseClasses());
            String name = baseClass.getName();
            int index = name.lastIndexOf("::");
            String baseClassSimpleName = (index > 0) ? name.substring(index + 2) : name;
            if (baseClassSimpleName.equals(J_OBJECT_CLASS_NAME)) {
                return true;
            }
        }

        return false;
    }

    @Override
    public String generate(CPPClass construct) {
        StringBuilder sb = new StringBuilder();
        if (isObject(construct)) {
            sb.append("\nprivate:");
            sb.append("\nstatic ClassInfo __classInfo;");
            sb.append("\nObjectInfo __objectInfo;\n");
        }
        return sb.toString();
    }

}

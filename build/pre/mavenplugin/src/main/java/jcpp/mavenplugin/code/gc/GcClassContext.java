package jcpp.mavenplugin.code.gc;

import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Set;

import jcpp.parser.cpp.CPPBaseClass;
import jcpp.parser.cpp.CPPClass;
import jcpp.parser.cpp.CPPField;
import jcpp.parser.cpp.CPPMethod;
import jcpp.parser.cpp.CPPType;

import org.eclipse.cdt.core.dom.ast.IFunction;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPMethod;

public class GcClassContext {
    private static final String J_OBJECT_CLASS_NAME = "JObject";

	private int nonStaticFieldCount;
	private int staticFieldCount;
	
	private boolean object;
	
	private Set<String> nonPureVirtualMethodNames;

	private CPPClass cppClass;
	
	public GcClassContext(CPPClass cppClass) {
		this.cppClass = cppClass;
		nonPureVirtualMethodNames = new HashSet<String>();
		
    	object = isObject(cppClass);
		
		List<CPPField> fields = cppClass.getFields();
    	for(CPPField field : fields) {
    		CPPType fieldType = field.getType();
			if(fieldType.isPointer()) {
				if(fieldType.isStatic()) {
					staticFieldCount++;	
				} else {
					nonStaticFieldCount++;
				}
			}
    	}
    	
        CPPMethod[] methods = cppClass.getMethods();
        for(CPPMethod cppMethod : methods) {
        	IFunction function = cppMethod.getFunction();
        	if(function instanceof ICPPMethod) {
        		ICPPMethod method = (ICPPMethod) function;
        		if(method.isPureVirtual()) {
        			continue;
        		}
        	}
        	String methodName = cppMethod.getName();
        	if(!methodName.contains(" ")) {
        		nonPureVirtualMethodNames.add(methodName);
        	}
        }
        
	}
	
	public CPPClass getCppClass() {
		return cppClass;
	}


	public boolean isObject() {
		return object;
	}

	public int getNonStaticFieldCount() {
		return nonStaticFieldCount;
	}

	public int getStaticFieldCount() {
		return staticFieldCount;
	}
	
	public Set<String> getNonPureVirtualMethodNames() {
		return nonPureVirtualMethodNames;
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

}

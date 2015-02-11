package jcpp.mavenplugin.code.gc;

import jcpp.parser.cpp.CPPClass;
import jcpp.parser.cpp.update.CodeGeneratorContext;
import jcpp.parser.cpp.update.ICodeGenerator;


public class GcClassCodeGenerator implements ICodeGenerator<CPPClass> {
    
	private final GcFileTupleContext gcContext;


    public GcClassCodeGenerator(GcFileTupleContext gcContext) {
		this.gcContext = gcContext;
    }

    @Override
    public String generate(CPPClass construct, CodeGeneratorContext context) {
    	GcClassContext classContext = gcContext.getClassContext(construct.getName());
    	
        StringBuilder sb = new StringBuilder();
        sb.append("\nprivate:");
        sb.append("\nstatic ClassInfo __classInfo;");
        
        for(String methodName : classContext.getNonPureVirtualMethodNames()) {
    		sb.append("\nstatic NativeString __");
        	if(methodName.startsWith("~")) {
        		sb.append("destructor").append(methodName.substring(1));
        	} else {
        		sb.append(methodName);
        	}
        	sb.append("MethodName;");
        }
        
        if (classContext.isObject()) {
        	int nonStaticFieldCount = classContext.getNonStaticFieldCount();
        	if(nonStaticFieldCount > 0) {
        		sb.append("\nFieldInfo* __fieldInfos[").append(nonStaticFieldCount).append("];\n");
        	}
            sb.append("\nObjectInfo __objectInfo;\n");
        }
        return sb.toString();
    }

}

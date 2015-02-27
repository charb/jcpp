package jcpp.mavenplugin.code.gc;

import java.util.List;

import jcpp.parser.cpp.CPPClass;
import jcpp.parser.cpp.CPPField;
import jcpp.parser.cpp.CPPFile;
import jcpp.parser.cpp.CPPMethod;
import jcpp.parser.cpp.update.CodeGeneratorContext;
import jcpp.parser.cpp.update.ICodeGenerator;


public class GcMemberInitializerCodeGenerator implements ICodeGenerator<CPPMethod> {

	private final GcFileTupleContext gcContext;


    public GcMemberInitializerCodeGenerator(GcFileTupleContext gcContext) {	
    	this.gcContext = gcContext;
    }


    @Override
    public String generate(CPPMethod construct, CodeGeneratorContext context) {
        String className = construct.getCppClass().getName();
        CPPClass cppClass = null;

        CPPFile headerCppFile = gcContext.isHeaderUpdater() ? null : gcContext.getHeaderCPPFile();
        if (headerCppFile != null) {
            cppClass = headerCppFile.getClass(className);
        }
        if (cppClass == null) {
            cppClass = construct.getCppClass();
        }

        if (cppClass != null) {
        	GcClassContext classContext = gcContext.getClassContext(cppClass.getName());
        	if((classContext != null) && classContext.isObject()) {
	        	StringBuilder sb = new StringBuilder();
	            int nonStaticFieldCount = classContext.getNonStaticFieldCount();
				sb.append("__objectInfo(&__classInfo, this, ").append(nonStaticFieldCount).append(nonStaticFieldCount > 0 ? ", __fieldInfos" : ", null").append(")");
	            
	            List<CPPField> fields = cppClass.getFields();
	            for (CPPField field : fields) {
	                if (field.getType().isPointer() && !field.getType().isStatic()) {
	                	String fieldName = field.getName();
	                	sb.append(", __").append(fieldName).append("FieldInfo(&__").append(fieldName).append("FieldName, (void**)&").append(fieldName).append(")");
	                }
	            }
	            return sb.toString();
        	}
        }
        return null;
    }

}

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

	private final GcFileTupleContext gcContext;
	
    private final Set<String> namespacesUpdated;
    private final Set<String> classNamesWritten;


    public GcEndOfNamespaceCodeGenerator(GcFileTupleContext gcContext) {
        this.gcContext = gcContext;
		namespacesUpdated = gcContext.isHeaderUpdater() && (gcContext.getCppCPPFile() != null) ? null : new HashSet<String>();
        classNamesWritten = gcContext.isHeaderUpdater() && (gcContext.getCppCPPFile() != null) ? null : new HashSet<String>();
    }


    @Override
    public String generate(CPPNamespace construct, CodeGeneratorContext context) {
    	if(!gcContext.isHeaderUpdater() || (gcContext.getCppCPPFile() == null)) {
		    StringBuilder sb = new StringBuilder();
		
		    String namespace = construct.getName();
		    if (!namespacesUpdated.contains(namespace)) {
		        namespacesUpdated.add(namespace);
		
		        CPPFile headerCppFile = gcContext.getHeaderCPPFile();
		        if (headerCppFile != null) {
		            generateCodeForCppClasses(sb, namespace, headerCppFile.getClasses());
		        }
		
		        CPPFile cppCppFile = gcContext.getCppCPPFile();
		        if (cppCppFile != null) {
		            generateCodeForCppClasses(sb, namespace, cppCppFile.getClasses());
		        }
		
		    }
		
		    return sb.toString();
    	}
    	return null;
    }

    private void generateCodeForCppClasses(StringBuilder sb, String namespace, CPPClass[] classes) {
        if (classes != null) {
            for (CPPClass cppClass : classes) {
                String classNamespaceName = cppClass.getNamespaceName();
                if (classNamespaceName.equals(namespace)) {
                    String className = cppClass.getName();

                    if (!classNamesWritten.contains(className)) {
                        classNamesWritten.add(className);
                        
                        GcClassContext classContext = gcContext.getClassContext(className);
                        
                    	if(classContext == null) {
                    		continue;
                    	}

                        for(String methodName : classContext.getNonPureVirtualMethodNames()) {
                    		sb.append("\nNativeString ").append(className).append("::__");
                        	if(methodName.startsWith("~")) {
                        		sb.append("destructor").append(methodName.substring(1));
                        	} else {
                        		sb.append(methodName);
                        	}
                        	sb.append("MethodName(\"").append(methodName).append("\");");
                        }
                                                
                        sb.append("\nClassInfo ").append(className).append("::__classInfo(\"").append(classNamespaceName).append("\", \"").append(className).append("\"").append(",").append(classContext.getStaticFieldCount()).append(");\n");
                        List<CPPField> fields = cppClass.getFields();
                        int counter = 0;
                        for (int index = 0; index < fields.size(); index++) {
                        	CPPField field = fields.get(index);
                            CPPType type = field.getType();
                            if (type.isPointer() && type.isStatic()) {
	                            String fieldName = field.getName();
	                            sb.append("FieldInfo ").append(className).append("::__").append(fieldName).append("StaticFieldInfo(&__classInfo, new NativeString(\"").append(fieldName).append("\"), (void**)&").append(fieldName).append(",").append(counter++).append(");\n");
                            }
                        }
                        
                        if(classContext.isObject()) {
                        	for(CPPField field : fields) {
                        		CPPType fieldType = field.getType();
                				if(fieldType.isPointer() && !fieldType.isStatic()) {
                					String fieldName = field.getName();
    	                            sb.append("\nNativeString ").append(className).append("::__").append(fieldName).append("FieldName(\"").append(fieldName).append("\");");
                				}
                        	}
                        }
                    }
                }
            }
        }
    }

}

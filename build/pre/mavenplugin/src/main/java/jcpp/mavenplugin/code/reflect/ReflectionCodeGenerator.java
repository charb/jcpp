package jcpp.mavenplugin.code.reflect;

import java.io.File;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

import jcpp.mavenplugin.code.CppFileTuple;
import jcpp.mavenplugin.code.TemplateCodeGenerator;
import jcpp.mavenplugin.code.UpdaterContext;
import jcpp.mavenplugin.code.Utils;
import jcpp.mavenplugin.code.gc.GcClassContext;
import jcpp.mavenplugin.code.gc.GcFileTupleContext;


public class ReflectionCodeGenerator extends TemplateCodeGenerator<CppFileTuple> {
    private static final String REFLECTION_TEMPLATE_HEADER_RESOURCE = "ReflectionTemplate.ftl";

    private static ReflectionCodeGenerator instance;


    private ReflectionCodeGenerator() throws Exception {
        super(REFLECTION_TEMPLATE_HEADER_RESOURCE, null);
    }


    public static synchronized ReflectionCodeGenerator getInstance() {
        if (instance == null) {
            try {
                instance = new ReflectionCodeGenerator();
            } catch (Exception e) {
                throw new RuntimeException(e);
            }
        }
        return instance;
    }

    @Override
    public CppFileTuple generateCode(UpdaterContext updaterContext, CppFileTuple cppFileTuple) throws Exception {
        ReflectionModelBuilder modelBuilder = new ReflectionModelBuilder();
        modelBuilder.setCppFileTuple(cppFileTuple);
        ReflectionModel reflectionModel = modelBuilder.build(updaterContext);

        File generatedHeaderFile = generateHeaderFile(updaterContext, reflectionModel, cppFileTuple);

        CppFileTuple tuple = new CppFileTuple(cppFileTuple.getName() + "_Reflection", cppFileTuple.getNamespace(), generatedHeaderFile, null, null);
        
        if(updaterContext.isAddGCcode()) {
	        UpdaterContext newUpdaterContext = new UpdaterContext(updaterContext, updaterContext.isUpdateExportMacro(), true, false, updaterContext.getNewSrcDir(), updaterContext.getNewSrcDir(), updaterContext.getNewCppBaseDir(), updaterContext.getNewCppBaseDir(), updaterContext.getNewCppBaseDir(), updaterContext.getNewCppBaseDir());
	        newUpdaterContext.getParserBuilder().addIncludeDirectory(updaterContext.getOriginalHeaderBaseDir().getAbsolutePath());
	        
	        tuple.init(newUpdaterContext, null);
	        
	        tuple.parseFiles();
	        
	        GcFileTupleContext gcFileTupleContext = tuple.getGcFileTupleContext();
	        
	        Map<String, GcClassContext> classContexts = gcFileTupleContext.getClassContexts();
	        
	        Set<String> classNames = new HashSet<String>();
	        for(ClassModel classModel : reflectionModel.getClasses()) {
	        	String fullNamespace = "";
	        	for (String n : classModel.getNamespaces())
	        		fullNamespace += n + "::";
	        	classNames.add(fullNamespace + classModel.getClassName() + "Class");
	        }
	        for(String gcClassContextClassname : classContexts.keySet().toArray(new String[classContexts.size()])) {
	        	if(!classNames.contains(gcClassContextClassname)) {
	        		classContexts.remove(gcClassContextClassname);
	        	}
	        }
	        
	        tuple.update();
        }
        return tuple;
    }

    @Override
    protected String createRelativeHeaderFilePath(CppFileTuple cppFileTuple) {
        return Utils.createRelativeReflectionHeaderFilePath(cppFileTuple);
    }

    @Override
    protected String createRelativeCppFilePath(CppFileTuple cppFileTuple) {
        return null;
    }

}

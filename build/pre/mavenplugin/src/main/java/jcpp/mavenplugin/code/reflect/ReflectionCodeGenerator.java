package jcpp.mavenplugin.code.reflect;

import java.io.File;

import jcpp.mavenplugin.code.CppFileTuple;
import jcpp.mavenplugin.code.TemplateCodeGenerator;
import jcpp.mavenplugin.code.UpdaterContext;
import jcpp.mavenplugin.code.Utils;


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
        tuple.init(updaterContext, null);
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

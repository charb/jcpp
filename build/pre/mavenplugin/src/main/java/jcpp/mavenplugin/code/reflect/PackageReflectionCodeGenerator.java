package jcpp.mavenplugin.code.reflect;

import java.io.File;

import jcpp.mavenplugin.code.CppFileTuple;
import jcpp.mavenplugin.code.CppPackage;
import jcpp.mavenplugin.code.TemplateCodeGenerator;
import jcpp.mavenplugin.code.UpdaterContext;


public class PackageReflectionCodeGenerator extends TemplateCodeGenerator<CppPackage> {

    private static final String PACKAGE_TEMPLATE_HEADER_RESOURCE = "PackageHeaderTemplate.ftl";
    private static final String PACKAGE_TEMPLATE_CPP_RESOURCE = "PackageSourceTemplate.ftl";

    private static PackageReflectionCodeGenerator instance;


    public PackageReflectionCodeGenerator() throws Exception {
        super(PACKAGE_TEMPLATE_HEADER_RESOURCE, PACKAGE_TEMPLATE_CPP_RESOURCE);
    }


    public static synchronized PackageReflectionCodeGenerator getInstance() {
        if (instance == null) {
            try {
                instance = new PackageReflectionCodeGenerator();
            } catch (Exception e) {
                throw new RuntimeException(e);
            }
        }
        return instance;
    }

    @Override
    public CppFileTuple generateCode(UpdaterContext updaterContext, CppPackage cppPackage) throws Exception {
        String namespace = cppPackage.getNamespace();
        if (namespace.isEmpty()) {
            return null;
        }
        PackageModelBuilder modelBuilder = new PackageModelBuilder();
        modelBuilder.setGeneratedCodePrefix(updaterContext.getGeneratedCodePrefix());
        modelBuilder.setNamespace(cppPackage.getNamespace());
        modelBuilder.setName(cppPackage.getName());

        CppPackage parentPackage = cppPackage.getParentPackage();
        if ((parentPackage != null) && !parentPackage.getName().isEmpty()) {
            modelBuilder.setSuperPackageNamespace(parentPackage.getNamespace());
        }

        for (CppPackage subPackage : cppPackage.getSubPackages()) {
            modelBuilder.addSubPackageName(subPackage.getName());
        }

        for (CppFileTuple cppFileTuple : cppPackage.getCppFileTuples()) {
            modelBuilder.addTupleHistoryInfo(cppFileTuple.getNewTupleHistory().getTupleHistoryInfo());
        }

        PackageModel packageModel = modelBuilder.build();

        File generatedHeaderFile = generateHeaderFile(updaterContext, packageModel, cppPackage);
        File generateCppFile = generateCppFile(updaterContext, packageModel, cppPackage);

        CppFileTuple tuple = new CppFileTuple(createFileName(cppPackage, new StringBuilder()).toString(), cppPackage.getNamespace(), generatedHeaderFile, generateCppFile, null);
        tuple.init(updaterContext, null);
        return tuple;
    }

    protected static String createRelativeFilePath(CppPackage cppPackage, String suffix) {
        String namespace = cppPackage.getNamespace();
        if (namespace.isEmpty()) {
            return null;
        }
        StringBuilder pathBuilder = new StringBuilder();

        pathBuilder.append(namespace.replace("::", "/")).append("/");

        createFileName(cppPackage, pathBuilder);
        pathBuilder.append(suffix);

        return pathBuilder.toString();
    }

    protected static StringBuilder createFileName(CppPackage cppPackage, StringBuilder pathBuilder) {
        String generatedCodePrefix = cppPackage.getUpdaterContext().getGeneratedCodePrefix();
        if (generatedCodePrefix != null) {
            pathBuilder.append(generatedCodePrefix);
        }

        pathBuilder.append(cppPackage.getNamespace().replace("::", "_").toUpperCase()).append("_PACKAGE");
        return pathBuilder;
    }

    @Override
    protected String createRelativeHeaderFilePath(CppPackage cppPackage) {
        return createRelativeFilePath(cppPackage, ".h");
    }

    @Override
    protected String createRelativeCppFilePath(CppPackage cppPackage) {
        return createRelativeFilePath(cppPackage, ".cpp");
    }

}

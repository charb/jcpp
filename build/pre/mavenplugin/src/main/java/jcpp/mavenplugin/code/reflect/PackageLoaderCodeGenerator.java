package jcpp.mavenplugin.code.reflect;

import java.io.File;

import java.util.List;

import jcpp.mavenplugin.code.CppFileTuple;
import jcpp.mavenplugin.code.CppPackage;
import jcpp.mavenplugin.code.TemplateCodeGenerator;
import jcpp.mavenplugin.code.UpdaterContext;


public class PackageLoaderCodeGenerator extends TemplateCodeGenerator<CppPackage> {

    private static final String PACKAGE_LOADER_TEMPLATE_HEADER_RESOURCE = "PackageLoaderHeaderTemplate.ftl";
    private static final String PACKAGE_LOADER_TEMPLATE_CPP_RESOURCE = "PackageLoaderSourceTemplate.ftl";

    private static PackageLoaderCodeGenerator instance;


    public PackageLoaderCodeGenerator() throws Exception {
        super(PACKAGE_LOADER_TEMPLATE_HEADER_RESOURCE, PACKAGE_LOADER_TEMPLATE_CPP_RESOURCE);
    }


    public static synchronized PackageLoaderCodeGenerator getInstance() {
        if (instance == null) {
            try {
                instance = new PackageLoaderCodeGenerator();
            } catch (Exception e) {
                throw new RuntimeException(e);
            }
        }
        return instance;
    }

    @Override
    public CppFileTuple generateCode(UpdaterContext updaterContext, CppPackage cppPackage) throws Exception {
        String namespace = cppPackage.getNamespace();
        if (!namespace.isEmpty()) {
            return null;
        }

        List<CppPackage> subPackages = cppPackage.getSubPackages();
        if (subPackages.size() == 0) {
            return null;

        }
        PackageLoaderModelBuilder packageLoaderModelBuilder = new PackageLoaderModelBuilder();
        packageLoaderModelBuilder.setRootPackage(subPackages.get(0));
        packageLoaderModelBuilder.setGeneratedCodePrefix(updaterContext.getGeneratedCodePrefix());

        PackageLoaderModel packageLoaderModel = packageLoaderModelBuilder.build();

        File generatedHeaderFile = generateHeaderFile(updaterContext, packageLoaderModel, cppPackage);
        File generateCppFile = generateCppFile(updaterContext, packageLoaderModel, cppPackage);

        CppFileTuple tuple = new CppFileTuple(createFileName(cppPackage, new StringBuilder()).toString(), cppPackage.getNamespace(), generatedHeaderFile, generateCppFile, null);
        tuple.init(updaterContext, null);
        return tuple;
    }

    protected static String createRelativeFilePath(CppPackage cppPackage, String suffix) {
        String namespace = cppPackage.getNamespace();
        if (!namespace.isEmpty()) {
            return null;
        }
        StringBuilder pathBuilder = new StringBuilder();

        createFileName(cppPackage, pathBuilder);
        pathBuilder.append(suffix);

        return pathBuilder.toString();
    }

    protected static StringBuilder createFileName(CppPackage cppPackage, StringBuilder pathBuilder) {
        String generatedCodePrefix = cppPackage.getUpdaterContext().getGeneratedCodePrefix();
        if (generatedCodePrefix != null) {
            pathBuilder.append(generatedCodePrefix);
        }

        pathBuilder.append("PackageLoader");
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

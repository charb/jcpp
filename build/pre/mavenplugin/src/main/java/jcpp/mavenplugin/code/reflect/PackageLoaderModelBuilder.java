package jcpp.mavenplugin.code.reflect;

import jcpp.mavenplugin.code.CppPackage;


public class PackageLoaderModelBuilder {

    private CppPackage rootPackage;

    private String generatedCodePrefix;


    public PackageLoaderModelBuilder() {
    }


    public PackageLoaderModel build() {
        String updatedName = (generatedCodePrefix == null) ? "PackageLoader" : (generatedCodePrefix + "PackageLoader");
        PackageLoaderModel packageLoaderModel = new PackageLoaderModel(updatedName);

        packageLoaderModel.setHeaderIncludePath(updatedName + ".h");

        String updatedPackageName = (generatedCodePrefix == null) ? rootPackage.getName().toUpperCase() : ((generatedCodePrefix + rootPackage.getName().toUpperCase()) + "_PACKAGE");
        packageLoaderModel.setPackageName(rootPackage.getNamespace().isEmpty() ? updatedPackageName : (rootPackage.getNamespace() + "::" + updatedPackageName));

        String packageHeaderIncludePath = rootPackage.getNamespace().isEmpty() ? (updatedPackageName + ".h") : (rootPackage.getNamespace().replace("::", "/") + "/" + updatedPackageName + ".h");
        packageLoaderModel.setPackageHeaderIncludePath(packageHeaderIncludePath);

        return packageLoaderModel;
    }

    public CppPackage getRootPackage() {
        return rootPackage;
    }

    public void setRootPackage(CppPackage rootPackage) {
        this.rootPackage = rootPackage;
    }

    public String getGeneratedCodePrefix() {
        return generatedCodePrefix;
    }

    public void setGeneratedCodePrefix(String generatedCodePrefix) {
        this.generatedCodePrefix = generatedCodePrefix;
    }

}

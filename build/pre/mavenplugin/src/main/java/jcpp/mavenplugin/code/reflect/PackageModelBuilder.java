package jcpp.mavenplugin.code.reflect;

import java.util.ArrayList;
import java.util.List;

import jcpp.mavenplugin.code.history.ClassHistoryInfo;
import jcpp.mavenplugin.code.history.TupleHistoryInfo;


public class PackageModelBuilder {

    private String generatedCodePrefix;

    private String name;

    private String namespace;

    private String superPackageNamespace;

    private List<String> subPackageNames;

    private List<TupleHistoryInfo> tupleHistoryInfos;


    public PackageModelBuilder() {
        subPackageNames = new ArrayList<String>();
        tupleHistoryInfos = new ArrayList<TupleHistoryInfo>();
    }


    public PackageModel build() {
        String updatedName = (generatedCodePrefix == null) ? name.toUpperCase() : ((generatedCodePrefix + namespace.replace("::", "_").toUpperCase()) + "_PACKAGE");

        PackageModel packageModel = new PackageModel(updatedName, namespace.replace("::", "."));
        packageModel.setHeaderIncludePath(namespace.isEmpty() ? (updatedName + ".h") : (namespace.replace("::", "/") + "/" + updatedName + ".h"));

        String[] namespaces = namespace.split("::");
        for (String nspace : namespaces) {
            packageModel.addNamespace(nspace);
        }

        if (superPackageNamespace != null) {
            int index = superPackageNamespace.lastIndexOf("::");
            String superPackageName = (index > 0) ? superPackageNamespace.substring(index + 2) : superPackageNamespace;
            String superPackageUpdatedName = (generatedCodePrefix == null) ? superPackageName.toUpperCase() : ((generatedCodePrefix + superPackageNamespace.replace("::", "_").toUpperCase()) + "_PACKAGE");
            PackageModel superPackageModel = new PackageModel(superPackageUpdatedName, superPackageNamespace.replace("::", "."));
            superPackageModel.setHeaderIncludePath(superPackageNamespace.replace("::", "/") + "/" + superPackageUpdatedName + ".h");
            packageModel.setSuperPackage(superPackageModel);
        }

        for (String subPackName : subPackageNames) {
            String updatedSubPackName = (generatedCodePrefix == null) ? subPackName.toUpperCase() : ((generatedCodePrefix + namespace.replace("::", "_").toUpperCase() + "_" + subPackName.toUpperCase()) + "_PACKAGE");
            PackageModel subPackage = new PackageModel(updatedSubPackName, namespace.replace("::", ".") + "." + subPackName);
            subPackage.setHeaderIncludePath((namespace + "::" + subPackName).replace("::", "/") + "/" + updatedSubPackName + ".h");
            packageModel.addSubPackages(subPackage);
        }

        for (TupleHistoryInfo tupleHistoryInfo : tupleHistoryInfos) {

            String tupleHistoryNamespace = tupleHistoryInfo.getNamespace();
            String headerIncludePath = (((tupleHistoryNamespace == null) || tupleHistoryNamespace.isEmpty()) ? tupleHistoryInfo.getName() : (tupleHistoryNamespace + "::" + tupleHistoryInfo.getName())).replace("::", "/") +
                ".h";

            for (ClassHistoryInfo classHistoryInfo : tupleHistoryInfo.getClassHistoryInfos()) {

                String subClassNamespace = classHistoryInfo.getNamespace();
                String subClassName = ((subClassNamespace == null) || subClassNamespace.isEmpty()) ? classHistoryInfo.getName() : (subClassNamespace + "::" + classHistoryInfo.getName());

                packageModel.addSubClass(new PackageClassModel(subClassName, headerIncludePath));
            }
        }

        return packageModel;
    }

    public String getNamespace() {
        return namespace;
    }

    public PackageModelBuilder setNamespace(String namespace) {
        this.namespace = namespace;
        return this;
    }

    public String getSuperPackageNamespace() {
        return superPackageNamespace;
    }

    public PackageModelBuilder setSuperPackageNamespace(String superPackageNamespace) {
        this.superPackageNamespace = superPackageNamespace;
        return this;
    }

    public PackageModelBuilder addSubPackageName(String subPackageName) {
        subPackageNames.add(subPackageName);
        return this;
    }

    public List<String> getSubPackageNames() {
        return subPackageNames;
    }

    public PackageModelBuilder setSubPackageNames(List<String> subPackageNames) {
        this.subPackageNames = subPackageNames;
        return this;
    }

    public List<TupleHistoryInfo> getTupleHistoryInfos() {
        return tupleHistoryInfos;
    }

    public PackageModelBuilder setTupleHistoryInfos(List<TupleHistoryInfo> tupleHistoryInfos) {
        this.tupleHistoryInfos = tupleHistoryInfos;
        return this;
    }

    public PackageModelBuilder addTupleHistoryInfo(TupleHistoryInfo tupleHistoryInfo) {
        if (tupleHistoryInfo != null) {
            tupleHistoryInfos.add(tupleHistoryInfo);
        }
        return this;
    }

    public String getName() {
        return name;
    }

    public PackageModelBuilder setName(String name) {
        this.name = name;
        return this;
    }

    public String getGeneratedCodePrefix() {
        return generatedCodePrefix;
    }

    public void setGeneratedCodePrefix(String generatedCodePrefix) {
        this.generatedCodePrefix = generatedCodePrefix;
    }

}

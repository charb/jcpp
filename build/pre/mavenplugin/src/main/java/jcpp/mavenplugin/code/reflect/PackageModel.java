package jcpp.mavenplugin.code.reflect;

import java.util.ArrayList;
import java.util.List;


public class PackageModel {

    private String name;
    private String packageName;
    private String qualifiedName;
    private String headerIncludePath;
    private PackageModel superPackage;
    private List<String> namespaces;
    private List<PackageModel> subPackages;
    private List<PackageClassModel> subClasses;


    public PackageModel(String name, String packageName) {
        this.name = name;
        this.packageName = packageName;
        this.qualifiedName = ((packageName == null) || packageName.isEmpty()) ? name : (packageName.replace(".", "::") + "::" + name);
        this.namespaces = new ArrayList<String>();
        this.subPackages = new ArrayList<PackageModel>();
        this.subClasses = new ArrayList<PackageClassModel>();
    }


    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getPackageName() {
        return packageName;
    }

    public void setPackageName(String packageName) {
        this.packageName = packageName;
    }

    public List<String> getNamespaces() {
        return namespaces;
    }

    public void setNamespaces(List<String> namespaces) {
        this.namespaces = namespaces;
    }

    public void addNamespace(String namespace) {
        namespaces.add(namespace);
    }

    public String getHeaderIncludePath() {
        return headerIncludePath;
    }

    public void setHeaderIncludePath(String headerIncludePath) {
        this.headerIncludePath = headerIncludePath;
    }

    public boolean isHasSuperPackage() {
        return superPackage != null;
    }

    public PackageModel getSuperPackage() {
        return superPackage;
    }

    public void setSuperPackage(PackageModel superPackage) {
        this.superPackage = superPackage;
    }

    public List<PackageClassModel> getSubClasses() {
        return subClasses;
    }

    public void setSubClasses(List<PackageClassModel> subClasses) {
        this.subClasses = subClasses;
    }

    public void addSubClass(PackageClassModel subClass) {
        this.subClasses.add(subClass);
    }

    public boolean isHasSubPackages() {
        return subPackages.size() > 0;
    }

    public List<PackageModel> getSubPackages() {
        return subPackages;
    }

    public void setSubPackages(List<PackageModel> subPackages) {
        this.subPackages = subPackages;
    }

    public void addSubPackages(PackageModel subPackage) {
        this.subPackages.add(subPackage);
    }

    public String getQualifiedName() {
        return qualifiedName;
    }

    public void setQualifiedName(String qualifiedName) {
        this.qualifiedName = qualifiedName;
    }

}

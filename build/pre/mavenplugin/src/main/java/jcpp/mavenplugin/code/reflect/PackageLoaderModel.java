package jcpp.mavenplugin.code.reflect;

public class PackageLoaderModel {

    private String name;
    private String packageName;
    private String headerIncludePath;
    private String packageHeaderIncludePath;


    public PackageLoaderModel(String name) {
        this.name = name;
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

    public String getHeaderIncludePath() {
        return headerIncludePath;
    }

    public void setHeaderIncludePath(String headerIncludePath) {
        this.headerIncludePath = headerIncludePath;
    }

    public String getPackageHeaderIncludePath() {
        return packageHeaderIncludePath;
    }

    public void setPackageHeaderIncludePath(String packageHeaderIncludePath) {
        this.packageHeaderIncludePath = packageHeaderIncludePath;
    }

}

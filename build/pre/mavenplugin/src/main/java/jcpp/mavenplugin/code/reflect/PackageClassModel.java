package jcpp.mavenplugin.code.reflect;

public class PackageClassModel {

    private String name;
    private String headerIncludePath;


    public PackageClassModel() {
    }

    public PackageClassModel(String name, String headerIncludePath) {
        this.name = name;
        this.headerIncludePath = headerIncludePath;
    }


    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getHeaderIncludePath() {
        return headerIncludePath;
    }

    public void setHeaderIncludePath(String headerIncludePath) {
        this.headerIncludePath = headerIncludePath;
    }

}

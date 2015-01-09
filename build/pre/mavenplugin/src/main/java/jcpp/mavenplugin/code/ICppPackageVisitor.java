package jcpp.mavenplugin.code;

public interface ICppPackageVisitor {

    void startCppPackage(CppPackage cppPackage);

    void visitCppFileTuple(CppFileTuple cppFileTuple);

    void endCppPackage(CppPackage cppPackage);

}

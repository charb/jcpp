package jcpp.mavenplugin.code;

public interface ICppCodeGenerator<T> {

    CppFileTuple generateCode(UpdaterContext updaterContext, T t) throws Exception;

}

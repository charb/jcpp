package jcpp.parser.cpp.update;

public interface IEnhancedCodeGenerator<T> extends ICodeGenerator<T> {

    public String generateBefore(T construct);

    public String generateAfter(T construct);

}

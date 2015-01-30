package jcpp.parser.cpp.update;

public interface IEnhancedCodeGenerator<T> extends ICodeGenerator<T> {

    public String generateBefore(T construct, CodeGeneratorContext context);

    public String generateAfter(T construct, CodeGeneratorContext context);

}

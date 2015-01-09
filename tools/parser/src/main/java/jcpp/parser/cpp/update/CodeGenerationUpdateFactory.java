package jcpp.parser.cpp.update;

import java.util.List;

public abstract class CodeGenerationUpdateFactory<T> extends UpdateFactory {

    protected ICodeGenerator<T> codeGenerator;
    protected List<String> includes;
    protected Updater updater;


    public CodeGenerationUpdateFactory(ICodeGenerator<T> codeGenerator, List<String> includes, Updater updater) {
        super();
        this.codeGenerator = codeGenerator;
        this.includes = includes;
        this.updater = updater;
    }

}

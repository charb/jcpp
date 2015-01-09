package jcpp.parser.cpp.update;

import java.util.List;

import org.eclipse.cdt.core.dom.ast.IASTNode;


public abstract class CodeGenerationUpdate<T> extends Update {

    protected ICodeGenerator<T> codeGenerator;
    protected List<String> includes;
    protected Updater updater;


    public CodeGenerationUpdate(IASTNode node, ICodeGenerator<T> codeGenerator, List<String> includes, Updater updater) {
        super(node);
        this.codeGenerator = codeGenerator;
        this.includes = includes;
        this.updater = updater;
    }

    public CodeGenerationUpdate(int manualOffset, ICodeGenerator<T> codeGenerator, List<String> includes, Updater updater) {
        super(manualOffset);
        this.codeGenerator = codeGenerator;
        this.includes = includes;
        this.updater = updater;
    }

}

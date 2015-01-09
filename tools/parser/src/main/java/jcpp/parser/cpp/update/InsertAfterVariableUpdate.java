package jcpp.parser.cpp.update;

import java.util.List;

import jcpp.parser.cpp.CPPVariable;

import org.eclipse.cdt.core.dom.ast.IASTDeclaration;


public class InsertAfterVariableUpdate extends CodeGenerationUpdate<CPPVariable> {

    private CPPVariable cppVariable;


    public InsertAfterVariableUpdate(CPPVariable cppVariable, ICodeGenerator<CPPVariable> codeGenerator, List<String> includes, Updater updater) {
        super(cppVariable.getDeclaration(), codeGenerator, includes, updater);
        this.cppVariable = cppVariable;
    }


    @Override
    public void update(UpdatesResult updatesResult) throws Exception {
        IASTDeclaration declaration = cppVariable.getDeclaration();
        int insertOffset = declaration.getFileLocation().getNodeOffset() + declaration.getFileLocation().getNodeLength();
        String generatedCode = codeGenerator.generate(cppVariable);
        if ((generatedCode != null) && !generatedCode.isEmpty()) {
            updater.insertIncludes(includes);
            updatesResult.insert(insertOffset, generatedCode);
        }
    }

}

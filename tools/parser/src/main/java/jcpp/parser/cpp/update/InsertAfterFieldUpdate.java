package jcpp.parser.cpp.update;

import java.util.List;

import jcpp.parser.cpp.CPPField;

import org.eclipse.cdt.core.dom.ast.IASTSimpleDeclaration;


public class InsertAfterFieldUpdate extends CodeGenerationUpdate<CPPField> {

    private CPPField cppField;


    public InsertAfterFieldUpdate(CPPField cppField, ICodeGenerator<CPPField> codeGenerator, List<String> includes, Updater updater) {
        super(cppField.getSimpleDeclaration(), codeGenerator, includes, updater);
        this.cppField = cppField;
    }


    @Override
    public void update(UpdatesResult updatesResult) throws Exception {
        IASTSimpleDeclaration declaration = cppField.getSimpleDeclaration();
        int insertOffset = declaration.getFileLocation().getNodeOffset() + declaration.getFileLocation().getNodeLength();
        String generatedCode = codeGenerator.generate(cppField);
        if ((generatedCode != null) && !generatedCode.isEmpty()) {
            updater.insertIncludes(includes);
            updatesResult.insert(insertOffset, generatedCode);
        }
    }

}

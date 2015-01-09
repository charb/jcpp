package jcpp.parser.cpp.update;

import java.util.List;

import jcpp.parser.cpp.CPPVariable;

import org.eclipse.cdt.core.dom.ast.IASTFileLocation;


public class ForInitVariableUpdate extends CodeGenerationUpdate<CPPVariable> {

    public enum ForUpdateMode {
        BEFORE_BODY, AFTER_BODY, REPLACE_INITIALIZER
    }


    private ForUpdateMode mode;
    private CPPVariable cppVariable;


    public ForInitVariableUpdate(int manualOffset, ICodeGenerator<CPPVariable> codeGenerator, List<String> includes, Updater updater, ForUpdateMode mode, CPPVariable cppVariable) {
        super(manualOffset, codeGenerator, includes, updater);
        this.mode = mode;
        this.cppVariable = cppVariable;
    }


    @Override
    public void update(UpdatesResult updatesResult) throws Exception {
        switch (mode) {
        case BEFORE_BODY:
            updateBeforeForBody(updatesResult);
            break;
        case AFTER_BODY:
            updateAfteForBody(updatesResult);
            break;
        case REPLACE_INITIALIZER:
            updateForInitializer(updatesResult);
            break;
        }
    }

    private IEnhancedCodeGenerator<CPPVariable> getCodeGenerator() {
        return (IEnhancedCodeGenerator<CPPVariable>) codeGenerator;
    }

    private void updateBeforeForBody(UpdatesResult updatesResult) {
        String generatedCode = getCodeGenerator().generateBefore(cppVariable);
        if ((generatedCode != null) && !generatedCode.isEmpty()) {
            int insertOffset = cppVariable.getForLoopStatement().getFileLocation().getNodeOffset();
            updater.insertIncludes(includes);
            updatesResult.insert(insertOffset, generatedCode);
        }
    }

    private void updateAfteForBody(UpdatesResult updatesResult) {
        String generatedCode = getCodeGenerator().generateAfter(cppVariable);
        if ((generatedCode != null) && !generatedCode.isEmpty()) {
            IASTFileLocation fileLocation = cppVariable.getForLoopStatement().getFileLocation();
            int insertOffset = fileLocation.getNodeOffset() + fileLocation.getNodeLength();
            updater.insertIncludes(includes);
            updatesResult.insert(insertOffset, generatedCode);
        }
    }

    private void updateForInitializer(UpdatesResult updatesResult) {
        String generatedCode = getCodeGenerator().generate(cppVariable);
        if ((generatedCode != null) && !generatedCode.isEmpty()) {
            IASTFileLocation fileLocation = cppVariable.getDeclaration().getFileLocation();
            int startOffset = fileLocation.getNodeOffset();
            int endOffset = startOffset + fileLocation.getNodeLength();
            updater.insertIncludes(includes);
            updatesResult.replace(startOffset, endOffset, generatedCode);
        }
    }

}

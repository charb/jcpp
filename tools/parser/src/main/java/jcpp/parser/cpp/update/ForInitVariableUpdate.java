package jcpp.parser.cpp.update;

import java.util.List;

import jcpp.parser.cpp.CPPVariable;

import org.eclipse.cdt.core.dom.ast.IASTFileLocation;
import org.eclipse.cdt.core.dom.ast.IASTMacroExpansionLocation;
import org.eclipse.cdt.core.dom.ast.IASTNode;
import org.eclipse.cdt.core.dom.ast.IASTNodeLocation;
import org.eclipse.cdt.internal.core.dom.parser.ASTNode;


public class ForInitVariableUpdate extends CodeGenerationUpdate<CPPVariable> {

    public enum ForUpdateMode {
        BEFORE_BODY, AFTER_BODY, REPLACE_INITIALIZER
    }


    private ForUpdateMode mode;
    private CPPVariable cppVariable;


    public ForInitVariableUpdate(ICodeGenerator<CPPVariable> codeGenerator, List<String> includes, Updater updater, ForUpdateMode mode, CPPVariable cppVariable) {
        super(computeInsertOffset(cppVariable, mode), codeGenerator, includes, updater);
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
            int insertOffset = computeInsertOffset(cppVariable, ForUpdateMode.BEFORE_BODY);
            updater.insertIncludes(includes);
            updatesResult.insert(insertOffset, generatedCode);
        }
    }

    private void updateAfteForBody(UpdatesResult updatesResult) {
        String generatedCode = getCodeGenerator().generateAfter(cppVariable);
        if ((generatedCode != null) && !generatedCode.isEmpty()) {
            int insertOffset = computeInsertOffset(cppVariable, ForUpdateMode.AFTER_BODY);
            updater.insertIncludes(includes);
            updatesResult.insert(insertOffset, generatedCode);
        }
    }

    private void updateForInitializer(UpdatesResult updatesResult) {
        String generatedCode = getCodeGenerator().generate(cppVariable);
        if ((generatedCode != null) && !generatedCode.isEmpty()) {
            IASTFileLocation fileLocation = getFileLocation(cppVariable.getDeclaration());
            int startOffset = fileLocation.getNodeOffset();
            int endOffset = startOffset + fileLocation.getNodeLength();
            updater.insertIncludes(includes);
            updatesResult.replace(startOffset, endOffset, generatedCode);
        }
    }

    private static int computeInsertOffset(CPPVariable cppVariable, ForUpdateMode mode) {
        int insertOffset = -1;
        IASTFileLocation fileLocation = null;
        switch (mode) {
        case BEFORE_BODY:
            fileLocation = getFileLocation(cppVariable.getForLoopStatement());
            insertOffset = fileLocation.getNodeOffset();
            break;
        case AFTER_BODY:
            fileLocation = getFileLocation(cppVariable.getForLoopStatement());
            insertOffset = fileLocation.getNodeOffset() + fileLocation.getNodeLength();
            break;
        case REPLACE_INITIALIZER:
            fileLocation = getFileLocation(cppVariable.getDeclaration());
            insertOffset = fileLocation.getNodeOffset();
            break;
        }
        return insertOffset;
    }

    private static IASTFileLocation getFileLocation(IASTNode node) {
        IASTNodeLocation[] nodeLocations = node.getNodeLocations();
        IASTFileLocation fileLocation = null;
        if (nodeLocations.length == 1 && nodeLocations[0] instanceof IASTMacroExpansionLocation) {
            fileLocation = ((ASTNode) node).getImageLocation();
        } else {
            fileLocation = node.getFileLocation();
        }
        return fileLocation;
    }

}

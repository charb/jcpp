package jcpp.parser.cpp.update;

import java.util.List;

import jcpp.parser.cpp.CPPVariable;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.eclipse.cdt.core.dom.ast.IASTFileLocation;
import org.eclipse.cdt.core.dom.ast.IASTMacroExpansionLocation;
import org.eclipse.cdt.core.dom.ast.IASTNode;
import org.eclipse.cdt.core.dom.ast.IASTNodeLocation;
import org.eclipse.cdt.internal.core.dom.parser.ASTNode;


public class ForInitVariableUpdate extends CodeGenerationUpdate<CPPVariable> {
    private static final Log log = LogFactory.getLog(ForInitVariableUpdate.class);

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
            if (insertOffset >= 0) {
                updater.insertIncludes(includes);
                updatesResult.insert(insertOffset, generatedCode);
            } else {
                if (log.isWarnEnabled()) {
                    log.warn("Unable to apply update before for-loop body [" + generatedCode +  "] for [" + cppVariable + "]. Unknown insertion offset.");
                }
            }
        }
    }

    private void updateAfteForBody(UpdatesResult updatesResult) {
        String generatedCode = getCodeGenerator().generateAfter(cppVariable);
        if ((generatedCode != null) && !generatedCode.isEmpty()) {
            int insertOffset = computeInsertOffset(cppVariable, ForUpdateMode.AFTER_BODY);
            if (insertOffset >= 0) {
                updater.insertIncludes(includes);
                updatesResult.insert(insertOffset, generatedCode);
            } else {
                if (log.isWarnEnabled()) {
                    log.warn("Unable to apply update after for-loop body [" + generatedCode +  "] for [" + cppVariable + "]. Unknown insertion offset.");
                }
            }
        }
    }

    private void updateForInitializer(UpdatesResult updatesResult) {
        String generatedCode = getCodeGenerator().generate(cppVariable);
        if ((generatedCode != null) && !generatedCode.isEmpty()) {
            IASTFileLocation fileLocation = getFileLocation(cppVariable.getDeclaration());
            if (fileLocation != null) {
                int startOffset = fileLocation.getNodeOffset();
                int endOffset = startOffset + fileLocation.getNodeLength();
                updater.insertIncludes(includes);
                updatesResult.replace(startOffset, endOffset, generatedCode);
            } else {
                if (log.isWarnEnabled()) {
                    log.warn("Unable to replace for-initializer with [" + generatedCode +  "] for [" + cppVariable + "]. Unknown insertion offset.");
                }

            }
        }
    }

    private static int computeInsertOffset(CPPVariable cppVariable, ForUpdateMode mode) {
        int insertOffset = -1;
        IASTFileLocation fileLocation = null;
        switch (mode) {
        case BEFORE_BODY:
            fileLocation = getFileLocation(cppVariable.getForLoopStatement());
            insertOffset = fileLocation != null ? fileLocation.getNodeOffset() : -1;
            break;
        case AFTER_BODY:
            fileLocation = getFileLocation(cppVariable.getForLoopStatement());
            insertOffset = fileLocation != null ? (fileLocation.getNodeOffset() + fileLocation.getNodeLength()) : -1;
            break;
        case REPLACE_INITIALIZER:
            fileLocation = getFileLocation(cppVariable.getDeclaration());
            insertOffset = fileLocation != null ? fileLocation.getNodeOffset() : -1;
            break;
        }
        return insertOffset;
    }

    private static IASTFileLocation getFileLocation(IASTNode node) {
        IASTNodeLocation[] nodeLocations = node.getNodeLocations();
        IASTFileLocation fileLocation = null;
        if (nodeLocations.length == 1 && nodeLocations[0] instanceof IASTMacroExpansionLocation) {
            fileLocation = ((ASTNode) node).getImageLocation(); //NOTE: can return null when the cppVariable is declared in a marco definition.
        } else {
            fileLocation = node.getFileLocation();
        }
        return fileLocation;
    }

}

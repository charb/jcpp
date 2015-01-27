package jcpp.parser.cpp.update;

import java.util.List;

import jcpp.parser.cpp.CPPVariable;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.eclipse.cdt.core.dom.ast.IASTDeclaration;
import org.eclipse.cdt.core.dom.ast.IASTFileLocation;
import org.eclipse.cdt.core.dom.ast.IASTMacroExpansionLocation;
import org.eclipse.cdt.core.dom.ast.IASTNodeLocation;
import org.eclipse.cdt.internal.core.dom.parser.ASTNode;


public class InsertAfterVariableUpdate extends CodeGenerationUpdate<CPPVariable> {
    private static final Log log = LogFactory.getLog(InsertAfterVariableUpdate.class);

    private CPPVariable cppVariable;


    public InsertAfterVariableUpdate(CPPVariable cppVariable, ICodeGenerator<CPPVariable> codeGenerator, List<String> includes, Updater updater) {
        super(computeInsertOffset(cppVariable), codeGenerator, includes, updater);
        this.cppVariable = cppVariable;
    }


    @Override
    public void update(UpdatesResult updatesResult) throws Exception {
        String generatedCode = codeGenerator.generate(cppVariable);
        if ((generatedCode != null) && !generatedCode.isEmpty()) {
            int insertOffset = computeInsertOffset(cppVariable);
            if (insertOffset >= 0 ) {
                updater.insertIncludes(includes);
                updatesResult.insert(insertOffset, generatedCode);
            } else {
                if (log.isWarnEnabled()) {
                    log.warn("Unable to apply update [" + generatedCode +  "] for [" + cppVariable + "]. Unknown insertion offset.");
                }
            }
        }
    }

    private static int computeInsertOffset(CPPVariable cppVariable) {
        IASTDeclaration declaration = cppVariable.getDeclaration();
        IASTNodeLocation[] nodeLocations = declaration.getNodeLocations();
        IASTFileLocation fileLocation = null;
        if (nodeLocations.length == 1 && nodeLocations[0] instanceof IASTMacroExpansionLocation) {
            fileLocation = ((ASTNode) declaration).getImageLocation(); //NOTE: can return null when the cppVariable is declared in a marco definition.
        } else {
            fileLocation = declaration.getFileLocation();
        }
        return fileLocation != null ? (fileLocation.getNodeOffset() + fileLocation.getNodeLength()) : -1;
    }

}

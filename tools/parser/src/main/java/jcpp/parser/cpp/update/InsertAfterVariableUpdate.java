package jcpp.parser.cpp.update;

import java.util.List;

import jcpp.parser.cpp.CPPVariable;

import org.eclipse.cdt.core.dom.ast.IASTDeclaration;
import org.eclipse.cdt.core.dom.ast.IASTFileLocation;
import org.eclipse.cdt.core.dom.ast.IASTMacroExpansionLocation;
import org.eclipse.cdt.core.dom.ast.IASTNodeLocation;
import org.eclipse.cdt.internal.core.dom.parser.ASTNode;


public class InsertAfterVariableUpdate extends CodeGenerationUpdate<CPPVariable> {

    private CPPVariable cppVariable;


    public InsertAfterVariableUpdate(CPPVariable cppVariable, ICodeGenerator<CPPVariable> codeGenerator, List<String> includes, Updater updater) {
        super(computeInsertOffset(cppVariable), codeGenerator, includes, updater);
        this.cppVariable = cppVariable;
    }


    @Override
    public void update(UpdatesResult updatesResult) throws Exception {
        int insertOffset = computeInsertOffset(cppVariable);
        String generatedCode = codeGenerator.generate(cppVariable);
        if ((generatedCode != null) && !generatedCode.isEmpty()) {
            updater.insertIncludes(includes);
            updatesResult.insert(insertOffset, generatedCode);
        }
    }

    private static int computeInsertOffset(CPPVariable cppVariable) {
        IASTDeclaration declaration = cppVariable.getDeclaration();
        IASTNodeLocation[] nodeLocations = declaration.getNodeLocations();
        IASTFileLocation fileLocation = null;
        if (nodeLocations.length == 1 && nodeLocations[0] instanceof IASTMacroExpansionLocation) {
            fileLocation = ((ASTNode) declaration).getImageLocation();
        } else {
            fileLocation = declaration.getFileLocation();
        }
        return fileLocation.getNodeOffset() + fileLocation.getNodeLength();
    }

}

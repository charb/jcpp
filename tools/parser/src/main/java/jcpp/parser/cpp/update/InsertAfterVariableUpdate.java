package jcpp.parser.cpp.update;

import java.util.List;

import jcpp.parser.cpp.CPPVariable;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.eclipse.cdt.core.dom.ast.IASTFileLocation;


public class InsertAfterVariableUpdate extends CodeGenerationUpdate<CPPVariable> {
    private static final Log log = LogFactory.getLog(InsertAfterVariableUpdate.class);

    private CPPVariable cppVariable;


    public InsertAfterVariableUpdate(CPPVariable cppVariable, ICodeGenerator<CPPVariable> codeGenerator, List<String> includes, Updater updater) {
        super(computeInsertOffset(cppVariable), codeGenerator, includes, updater);
        this.cppVariable = cppVariable;
    }


    @Override
    public void update(UpdatesResult updatesResult) throws Exception {
        CodeGeneratorContext context = new CodeGeneratorContext(cppVariable.getDeclaration(), updatesResult);
        String generatedCode = codeGenerator.generate(cppVariable, context);
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
        IASTFileLocation fileLocation = CodeGeneratorContext.getFileLocation(cppVariable.getDeclaration());
        return fileLocation != null ? (fileLocation.getNodeOffset() + fileLocation.getNodeLength()) : -1;
    }

}

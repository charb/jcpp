package jcpp.parser.cpp.update;

import java.util.List;

import jcpp.parser.cpp.CPPMethod;

import org.eclipse.cdt.core.dom.ast.IASTStatement;


public class InsertAfterMethodUpdate extends CodeGenerationUpdate<CPPMethod> {

    private CPPMethod cppMethod;


    public InsertAfterMethodUpdate(CPPMethod cppMethod, ICodeGenerator<CPPMethod> codeGenerator, List<String> includes, Updater updater) {
        super(cppMethod.getFunctionDefinition().getBody(), codeGenerator, includes, updater);
        this.cppMethod = cppMethod;
    }


    @Override
    public void update(UpdatesResult updatesResult) throws Exception {
        StringBuilder sb = new StringBuilder(System.lineSeparator());
        String generatedCode = codeGenerator.generate(cppMethod);
        if ((generatedCode != null) && !generatedCode.isEmpty()) {
            updater.insertIncludes(includes);
            sb.append(generatedCode);
            if (!generatedCode.endsWith(System.lineSeparator())) {
                sb.append(System.lineSeparator());
            }
        }

        IASTStatement bodyStatement = cppMethod.getFunctionDefinition().getBody();
        int insertOffset = bodyStatement.getFileLocation().getNodeOffset() + 1;
        updatesResult.insert(insertOffset, sb.toString());
    }

}

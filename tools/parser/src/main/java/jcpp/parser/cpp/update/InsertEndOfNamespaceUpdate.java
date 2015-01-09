package jcpp.parser.cpp.update;

import java.util.List;

import jcpp.parser.cpp.CPPNamespace;

import org.eclipse.cdt.core.dom.ast.IASTFileLocation;


public class InsertEndOfNamespaceUpdate extends CodeGenerationUpdate<CPPNamespace> {

    private CPPNamespace cppNamespace;


    public InsertEndOfNamespaceUpdate(CPPNamespace cppNamespace, ICodeGenerator<CPPNamespace> codeGenerator, List<String> includes, Updater updater) {
        super(computeInsertOffset(cppNamespace), codeGenerator, includes, updater);
        this.cppNamespace = cppNamespace;
    }


    @Override
    public void update(UpdatesResult updatesResult) throws Exception {
        String generatedCode = codeGenerator.generate(cppNamespace);
        if ((generatedCode != null) && !generatedCode.isEmpty()) {
            updater.insertIncludes(includes);

            StringBuilder sb = new StringBuilder(System.lineSeparator());
            sb.append(generatedCode);
            if (!generatedCode.endsWith(System.lineSeparator())) {
                sb.append(System.lineSeparator());
            }

            int insertOffset = computeInsertOffset(cppNamespace);

            updatesResult.insert(insertOffset, sb.toString());
        }
    }

    private static int computeInsertOffset(CPPNamespace cppNamespace) {
        IASTFileLocation fileLocation = cppNamespace.getNamespaceDefinition().getFileLocation();
        return fileLocation.getNodeOffset() + fileLocation.getNodeLength() - 1;
    }

}

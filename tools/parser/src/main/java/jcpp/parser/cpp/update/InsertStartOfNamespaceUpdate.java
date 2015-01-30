package jcpp.parser.cpp.update;

import java.util.List;

import jcpp.parser.cpp.CPPNamespace;

import org.eclipse.cdt.core.dom.ast.IASTName;


public class InsertStartOfNamespaceUpdate extends CodeGenerationUpdate<CPPNamespace> {

    private CPPNamespace cppNamespace;


    public InsertStartOfNamespaceUpdate(CPPNamespace cppNamespace, ICodeGenerator<CPPNamespace> codeGenerator, List<String> includes, Updater updater) {
        super(cppNamespace.getNamespaceDefinition(), codeGenerator, includes, updater);
        this.cppNamespace = cppNamespace;
    }


    @Override
    public void update(UpdatesResult updatesResult) throws Exception {
        CodeGeneratorContext context = new CodeGeneratorContext(cppNamespace.getNamespaceDefinition(), updatesResult);
        String generatedCode = codeGenerator.generate(cppNamespace, context);
        if ((generatedCode != null) && !generatedCode.isEmpty()) {
            updater.insertIncludes(includes);

            StringBuilder sb = new StringBuilder(System.lineSeparator());
            sb.append(generatedCode);
            if (!generatedCode.endsWith(System.lineSeparator())) {
                sb.append(System.lineSeparator());
            }

            IASTName astName = cppNamespace.getNamespaceDefinition().getName();
            int insertOffset = astName.getFileLocation().getNodeOffset() + astName.getFileLocation().getNodeLength();
            while (updatesResult.charAt(insertOffset++) != '{') { }
            updatesResult.insert(insertOffset, sb.toString());
        }
    }

}

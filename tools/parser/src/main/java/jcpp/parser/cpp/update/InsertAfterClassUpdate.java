package jcpp.parser.cpp.update;

import java.util.List;

import jcpp.parser.cpp.CPPClass;

import org.eclipse.cdt.core.dom.ast.IASTName;


public class InsertAfterClassUpdate extends CodeGenerationUpdate<CPPClass> {

    private CPPClass cppClass;


    public InsertAfterClassUpdate(CPPClass cppClass, ICodeGenerator<CPPClass> codeGenerator, List<String> includes, Updater updater) {
        super(cppClass.getCompositeTypeSpecifier(), codeGenerator, includes, updater);
        this.cppClass = cppClass;
    }


    @Override
    public void update(UpdatesResult updatesResult) throws Exception {
        String generatedCode = codeGenerator.generate(cppClass);
        if ((generatedCode != null) && !generatedCode.isEmpty()) {
            updater.insertIncludes(includes);

            StringBuilder sb = new StringBuilder(System.lineSeparator());
            sb.append(generatedCode);
            if (!generatedCode.endsWith(System.lineSeparator())) {
                sb.append(System.lineSeparator());
            }

            IASTName astName = cppClass.getCompositeTypeSpecifier().getName();
            int insertOffset = astName.getFileLocation().getNodeOffset() + astName.getFileLocation().getNodeLength();
            while (updatesResult.charAt(insertOffset++) != '{') {
                ;
            }

            updatesResult.insert(insertOffset, sb.toString());
        }
    }

}

package jcpp.parser.cpp.update;

import java.util.List;

import jcpp.parser.cpp.CPPMethod;

import org.eclipse.cdt.core.dom.ast.cpp.ICPPASTFunctionDefinition;


public class InsertMemberInitializersUpdate extends CodeGenerationUpdate<CPPMethod> {

    private CPPMethod cppMethod;


    public InsertMemberInitializersUpdate(CPPMethod cppMethod, ICodeGenerator<CPPMethod> codeGenerator, List<String> includes, Updater updater) {
        super(cppMethod.getFunctionDefinition(), codeGenerator, includes, updater);
        this.cppMethod = cppMethod;
    }


    @Override
    public void update(UpdatesResult updatesResult) throws Exception {
        String generatedCode = codeGenerator.generate(cppMethod);
        if ((generatedCode != null) && !generatedCode.isEmpty()) {
            updater.insertIncludes(includes);
            ICPPASTFunctionDefinition definition = (ICPPASTFunctionDefinition) cppMethod.getFunctionDefinition();

            String content = updatesResult.getContent();
            int methodNodeOffset = definition.getFileLocation().getNodeOffset();
            int bracketIndex = content.indexOf("{", methodNodeOffset);
            if ((bracketIndex < 0) || (bracketIndex > (methodNodeOffset + definition.getFileLocation().getNodeLength()))) {
                return;
            }
            int insertOffset = bracketIndex;

            boolean memberInitializersExist = false;
            int methodDeclarationEndIndex = content.indexOf(")", methodNodeOffset);
            int currentIndex = methodDeclarationEndIndex + 1;
            while (currentIndex < insertOffset) {
                char ch = content.charAt(currentIndex++);
                if (!Character.isWhitespace(ch)) {
                    memberInitializersExist = ch != '{';
                    break;
                }
            }

            StringBuilder sb = new StringBuilder();
            if (memberInitializersExist) {
                sb.append(",");
            } else {
                sb.append(":");
            }

            sb.append(generatedCode);
            sb.append(" ");
            updatesResult.insert(insertOffset, sb.toString());

        }
    }

}

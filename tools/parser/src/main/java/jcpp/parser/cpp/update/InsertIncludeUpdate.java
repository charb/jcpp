package jcpp.parser.cpp.update;

import java.util.Set;

import org.eclipse.cdt.core.dom.ast.IASTFileLocation;
import org.eclipse.cdt.core.dom.ast.IASTPreprocessorFunctionStyleMacroDefinition;
import org.eclipse.cdt.core.dom.ast.IASTPreprocessorIncludeStatement;
import org.eclipse.cdt.core.dom.ast.IASTPreprocessorMacroDefinition;
import org.eclipse.cdt.core.dom.ast.IASTPreprocessorObjectStyleMacroDefinition;
import org.eclipse.cdt.core.dom.ast.IASTPreprocessorStatement;
import org.eclipse.cdt.core.dom.ast.IASTTranslationUnit;

import jcpp.parser.cpp.CPPFile;


public class InsertIncludeUpdate extends Update {

    private Set<String> includes;
    private CPPFile cppFile;
    private boolean atEndOfFile;


    public InsertIncludeUpdate(Set<String> includes, CPPFile cppFile, boolean atEndOfFile) {
        super(computeOffset(cppFile, atEndOfFile));
        this.includes = includes;
        this.cppFile = cppFile;
        this.atEndOfFile = atEndOfFile;
    }


    @Override
    public void update(UpdatesResult updatesResult) throws Exception {
        StringBuilder sb = new StringBuilder();
        sb.append(System.lineSeparator());
        for (String include : includes) {
            sb.append("#include \"").append(include).append("\"").append(System.lineSeparator());
        }
        int insertOffset = computeOffset(cppFile, atEndOfFile);
        updatesResult.insert(insertOffset, sb.toString());
    }

    private static int computeOffset(CPPFile cppFile, boolean atEndOfFile) {
        IASTTranslationUnit translationUnit = cppFile.getTranslationUnit();
        IASTPreprocessorStatement preprocessorStatement = null;
        IASTFileLocation fileLocation = null;
        if (atEndOfFile) {
            return translationUnit.getFileLocation().getNodeLength();
        } else {
            preprocessorStatement = findLastInclude(translationUnit);
            if (preprocessorStatement == null) {
                preprocessorStatement = findFirstDefine(translationUnit);
            }
            if (preprocessorStatement != null) {
                fileLocation = preprocessorStatement.getFileLocation();
            }
            return fileLocation != null ? fileLocation.getNodeOffset() + fileLocation.getNodeLength() : 0;
        }
    }

    private static IASTPreprocessorObjectStyleMacroDefinition findFirstDefine(IASTTranslationUnit translationUnit) {
        IASTPreprocessorMacroDefinition[] macroDefinitions = translationUnit.getMacroDefinitions();
        IASTPreprocessorObjectStyleMacroDefinition macroDefinition = null;
        for (int i = 0; i < macroDefinitions.length; i++) {
            if (macroDefinitions[i].getContainingFilename().equals(translationUnit.getContainingFilename()) &&
                macroDefinitions[i].getExpansion().isEmpty() &&
                !(macroDefinitions[i] instanceof IASTPreprocessorFunctionStyleMacroDefinition)) {
                macroDefinition = (IASTPreprocessorObjectStyleMacroDefinition) macroDefinitions[i];
                break;
            }
        }
        return macroDefinition;
    }

    private static IASTPreprocessorIncludeStatement findLastInclude(IASTTranslationUnit translationUnit) {
        IASTPreprocessorIncludeStatement[] includeDirectives = translationUnit.getIncludeDirectives();
        IASTPreprocessorIncludeStatement includeDirective = null;
        for (int i = includeDirectives.length - 1; i >= 0; i--) {
            if (includeDirectives[i].getContainingFilename().equals(translationUnit.getContainingFilename())) {
                includeDirective = includeDirectives[i];
                break;
            }
        }
        return includeDirective;
    }

}

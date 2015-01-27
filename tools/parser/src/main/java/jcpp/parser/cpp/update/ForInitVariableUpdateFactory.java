package jcpp.parser.cpp.update;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

import jcpp.parser.cpp.CPPClass;
import jcpp.parser.cpp.CPPFile;
import jcpp.parser.cpp.CPPMethod;
import jcpp.parser.cpp.CPPVariable;
import jcpp.parser.cpp.update.ForInitVariableUpdate.ForUpdateMode;

import org.eclipse.cdt.core.dom.ast.IASTFileLocation;


public class ForInitVariableUpdateFactory extends CodeGenerationUpdateFactory<CPPVariable> {

    public ForInitVariableUpdateFactory(IEnhancedCodeGenerator<CPPVariable> codeGenerator, List<String> includes, Updater updater) {
        super(codeGenerator, includes, updater);
    }


    @Override
    public List<Update> createUpdates(CPPFile cppFile) throws Exception {
        List<Update> updates = new ArrayList<Update>();
        for (CPPClass cppClass : cppFile.getClasses()) {
            for (CPPMethod cppMethod : cppClass.getMethods()) {
                for (CPPVariable cppVariable : cppMethod.getVariables()) {
                    updates.addAll(createUpdates(cppVariable));
                }
            }
        }
        for (CPPMethod cppMethod : cppFile.getFunctions()) {
            for (CPPVariable cppVariable : cppMethod.getVariables()) {
                updates.addAll(createUpdates(cppVariable));
            }
        }
        return updates;
    }

    private List<Update> createUpdates(CPPVariable cppVariable) {
        if (!cppVariable.isForLoopInitializer()) {
            return Collections.emptyList();
        }
        Update beforeForBody = new ForInitVariableUpdate(codeGenerator, includes, updater, ForUpdateMode.BEFORE_BODY, cppVariable);

        Update afterForBody = new ForInitVariableUpdate(codeGenerator, includes, updater, ForUpdateMode.AFTER_BODY, cppVariable);

        Update replaceForInit = new ForInitVariableUpdate(codeGenerator, includes, updater, ForUpdateMode.REPLACE_INITIALIZER, cppVariable);

        return Arrays.asList(beforeForBody, afterForBody, replaceForInit);
    }

}

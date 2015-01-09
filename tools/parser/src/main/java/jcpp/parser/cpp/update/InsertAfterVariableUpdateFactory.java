package jcpp.parser.cpp.update;

import java.util.ArrayList;
import java.util.List;

import jcpp.parser.cpp.CPPClass;
import jcpp.parser.cpp.CPPFile;
import jcpp.parser.cpp.CPPMethod;
import jcpp.parser.cpp.CPPVariable;


public class InsertAfterVariableUpdateFactory extends CodeGenerationUpdateFactory<CPPVariable> {

    public InsertAfterVariableUpdateFactory(ICodeGenerator<CPPVariable> codeGenerator, List<String> includes, Updater updater) {
        super(codeGenerator, includes, updater);
    }


    @Override
    public List<Update> createUpdates(CPPFile cppFile) throws Exception {
        List<Update> updates = new ArrayList<Update>();
        for (CPPClass cppClass : cppFile.getClasses()) {
            for (CPPMethod cppMethod : cppClass.getMethods()) {
                for (CPPVariable cppVariable : cppMethod.getVariables()) {
                    if (!cppVariable.isForLoopInitializer()) {
                        updates.add(new InsertAfterVariableUpdate(cppVariable, codeGenerator, includes, updater));
                    }
                }
            }
        }
        for (CPPMethod cppMethod : cppFile.getFunctions()) {
            for (CPPVariable cppVariable : cppMethod.getVariables()) {
                if (!cppVariable.isForLoopInitializer()) {
                    updates.add(new InsertAfterVariableUpdate(cppVariable, codeGenerator, includes, updater));
                }
            }
        }
        for (CPPVariable cppVariable : cppFile.getGlobalVariables()) {
            if (!cppVariable.isForLoopInitializer()) {
                updates.add(new InsertAfterVariableUpdate(cppVariable, codeGenerator, includes, updater));
            }
        }
        return updates;
    }

}

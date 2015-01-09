package jcpp.parser.cpp.update;

import java.util.ArrayList;
import java.util.List;

import jcpp.parser.cpp.CPPClass;
import jcpp.parser.cpp.CPPFile;
import jcpp.parser.cpp.CPPMethod;


public class InsertAfterMethodUpdateFactory extends CodeGenerationUpdateFactory<CPPMethod> {

    public InsertAfterMethodUpdateFactory(ICodeGenerator<CPPMethod> codeGenerator, List<String> includes, Updater updater) {
        super(codeGenerator, includes, updater);
    }


    @Override
    public List<Update> createUpdates(CPPFile cppFile) throws Exception {
        List<Update> updates = new ArrayList<Update>();
        for (CPPClass cppClass : cppFile.getClasses()) {
            for (CPPMethod cppMethod : cppClass.getMethods()) {
                if (cppMethod.isFunctionDefinition()) {
                    updates.add(new InsertAfterMethodUpdate(cppMethod, codeGenerator, includes, updater));
                }
            }
        }
        for (CPPMethod cppMethod : cppFile.getFunctions()) {
            if (cppMethod.isFunctionDefinition()) {
                updates.add(new InsertAfterMethodUpdate(cppMethod, codeGenerator, includes, updater));
            }
        }
        return updates;
    }

}

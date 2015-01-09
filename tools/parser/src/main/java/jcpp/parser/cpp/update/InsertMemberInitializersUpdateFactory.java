package jcpp.parser.cpp.update;

import java.util.ArrayList;
import java.util.List;

import jcpp.parser.cpp.CPPClass;
import jcpp.parser.cpp.CPPFile;
import jcpp.parser.cpp.CPPMethod;


public class InsertMemberInitializersUpdateFactory extends CodeGenerationUpdateFactory<CPPMethod> {

    public InsertMemberInitializersUpdateFactory(ICodeGenerator<CPPMethod> codeGenerator, List<String> includes, Updater updater) {
        super(codeGenerator, includes, updater);
    }


    @Override
    public List<Update> createUpdates(CPPFile cppFile) throws Exception {
        List<Update> updates = new ArrayList<Update>();
        for (CPPClass cppClass : cppFile.getClasses()) {
            for (CPPMethod cppMethod : cppClass.getMethods()) {
                if (cppMethod.isConstructor() && cppMethod.isFunctionDefinition()) {
                    updates.add(new InsertMemberInitializersUpdate(cppMethod, codeGenerator, includes, updater));
                }
            }
        }
        return updates;
    }

}

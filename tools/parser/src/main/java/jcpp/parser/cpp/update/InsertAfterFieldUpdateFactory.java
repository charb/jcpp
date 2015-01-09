package jcpp.parser.cpp.update;

import java.util.ArrayList;
import java.util.List;

import jcpp.parser.cpp.CPPClass;
import jcpp.parser.cpp.CPPField;
import jcpp.parser.cpp.CPPFile;


public class InsertAfterFieldUpdateFactory extends CodeGenerationUpdateFactory<CPPField> {

    public InsertAfterFieldUpdateFactory(ICodeGenerator<CPPField> codeGenerator, List<String> includes, Updater updater) {
        super(codeGenerator, includes, updater);
    }


    @Override
    public List<Update> createUpdates(CPPFile cppFile) throws Exception {
        List<Update> updates = new ArrayList<Update>();
        for (CPPClass cppClass : cppFile.getClasses()) {
            for (CPPField cppField : cppClass.getFields()) {
                updates.add(new InsertAfterFieldUpdate(cppField, codeGenerator, includes, updater));
            }
        }
        return updates;
    }

}

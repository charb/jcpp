package jcpp.parser.cpp.update;

import java.util.ArrayList;
import java.util.List;

import jcpp.parser.cpp.CPPClass;
import jcpp.parser.cpp.CPPFile;


public class InsertAfterClassUpdateFactory extends CodeGenerationUpdateFactory<CPPClass> {

    public InsertAfterClassUpdateFactory(ICodeGenerator<CPPClass> codeGenerator, List<String> includes, Updater updater) {
        super(codeGenerator, includes, updater);
    }


    @Override
    public List<Update> createUpdates(CPPFile cppFile) throws Exception {
        List<Update> updates = new ArrayList<Update>();
        for (CPPClass cppClass : cppFile.getClasses()) {
            if (cppClass.getCompositeTypeSpecifier() != null) {
                updates.add(new InsertAfterClassUpdate(cppClass, codeGenerator, includes, updater));
            }
        }
        return updates;
    }

}

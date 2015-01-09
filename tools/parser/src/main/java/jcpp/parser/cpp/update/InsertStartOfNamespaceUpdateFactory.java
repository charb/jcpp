package jcpp.parser.cpp.update;

import java.util.ArrayList;
import java.util.List;

import jcpp.parser.cpp.CPPFile;
import jcpp.parser.cpp.CPPNamespace;


public class InsertStartOfNamespaceUpdateFactory extends CodeGenerationUpdateFactory<CPPNamespace> {

    public InsertStartOfNamespaceUpdateFactory(ICodeGenerator<CPPNamespace> codeGenerator, List<String> includes, Updater updater) {
        super(codeGenerator, includes, updater);
    }


    @Override
    public List<Update> createUpdates(CPPFile cppFile) throws Exception {
        List<Update> updates = new ArrayList<Update>();
        for (CPPNamespace cppNamespace : cppFile.getNamespaces()) {
            updates.add(new InsertStartOfNamespaceUpdate(cppNamespace, codeGenerator, includes, updater));
        }
        return updates;
    }

}

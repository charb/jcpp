package jcpp.parser.cpp.update;

import java.util.ArrayList;
import java.util.List;
import java.util.Set;
import java.util.TreeSet;

import jcpp.parser.cpp.CPPClass;
import jcpp.parser.cpp.CPPField;
import jcpp.parser.cpp.CPPFile;
import jcpp.parser.cpp.CPPMethod;
import jcpp.parser.cpp.CPPNamespace;
import jcpp.parser.cpp.CPPVariable;


public class Updater {

    private List<UpdateFactory> updateFactories;
    private InsertIncludesUpdateFactory insertIncludesUpdateFactory;


    public Updater() {
        updateFactories = new ArrayList<UpdateFactory>();
    }


    public void replaceMacro(String macroToFind, String macroToInsert) {
        updateFactories.add(new ReplaceMacroFactory(macroToFind, macroToInsert));
    }

    public void addMemberInitializerCodeGenerator(ICodeGenerator<CPPMethod> codeGenerator, List<String> includes) {
        updateFactories.add(new InsertMemberInitializersUpdateFactory(codeGenerator, includes, this));
    }

    public void addVariableCodeGenerator(ICodeGenerator<CPPVariable> codeGenerator, List<String> includes) {
        updateFactories.add(new InsertAfterVariableUpdateFactory(codeGenerator, includes, this));
    }

    public void addMethodCodeGenerator(ICodeGenerator<CPPMethod> codeGenerator, List<String> includes) {
        updateFactories.add(new InsertAfterMethodUpdateFactory(codeGenerator, includes, this));
    }

    public void addFieldCodeGenerator(ICodeGenerator<CPPField> codeGenerator, List<String> includes) {
        updateFactories.add(new InsertAfterFieldUpdateFactory(codeGenerator, includes, this));
    }

    public void addEndOfNamespaceCodeGenerator(ICodeGenerator<CPPNamespace> codeGenerator, List<String> includes) {
        updateFactories.add(new InsertEndOfNamespaceUpdateFactory(codeGenerator, includes, this));
    }

    public void addStartOfNamespaceCodeGenerator(ICodeGenerator<CPPNamespace> codeGenerator, List<String> includes) {
        updateFactories.add(new InsertStartOfNamespaceUpdateFactory(codeGenerator, includes, this));
    }

    public void addClassCodeGenerator(ICodeGenerator<CPPClass> codeGenerator, List<String> includes) {
        updateFactories.add(new InsertAfterClassUpdateFactory(codeGenerator, includes, this));
    }

    public void addForStatementInitializerVariableCodeGenerator(IEnhancedCodeGenerator<CPPVariable> codeGenerator, List<String> includes) {
        updateFactories.add(new ForInitVariableUpdateFactory(codeGenerator, includes, this));
    }

    public void insertIncludes(List<String> includes) {
        if (insertIncludesUpdateFactory == null) {
            insertIncludesUpdateFactory = new InsertIncludesUpdateFactory();
        }
        insertIncludesUpdateFactory.addIncludes(includes);
    }

    public void insertEndOfFileIncludes(List<String> includes) {
        if (insertIncludesUpdateFactory == null) {
            insertIncludesUpdateFactory = new InsertIncludesUpdateFactory();
        }
        insertIncludesUpdateFactory.addEndOfFileIncludes(includes);
    }

    public void clear() {
        if (insertIncludesUpdateFactory != null) {
            insertIncludesUpdateFactory.clear();
        }
    }

    public UpdatesResult update(CPPFile cppFile) throws Exception {
        Set<Update> sortedUpdates = new TreeSet<Update>();

        for (UpdateFactory updateFactory : updateFactories) {
            List<Update> updates = updateFactory.createUpdates(cppFile);
            sortedUpdates.addAll(updates);
        }
        if (insertIncludesUpdateFactory != null) {
            List<Update> updates = insertIncludesUpdateFactory.createEndOfFileUpdates(cppFile);
            sortedUpdates.addAll(updates);
        }

        UpdatesResult updatesResult = new UpdatesResult(cppFile.getContent());

        for (Update update : sortedUpdates) {
            update.update(updatesResult);
        }

        if (insertIncludesUpdateFactory != null) { //TODO: has to be at after all other updates have executed because they determine what the includes are.
            List<Update> updates = insertIncludesUpdateFactory.createUpdates(cppFile);
            for (Update update : updates) {
                update.update(updatesResult);
            }
        }

        return updatesResult;
    }

    //TODO: add clear method
}

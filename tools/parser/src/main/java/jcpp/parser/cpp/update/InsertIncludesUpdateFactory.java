package jcpp.parser.cpp.update;

import java.util.Collection;
import java.util.Collections;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Set;

import jcpp.parser.cpp.CPPFile;


public class InsertIncludesUpdateFactory extends UpdateFactory {
    private Set<String> includes;
    private Set<String> endOfFileIncludes;


    public InsertIncludesUpdateFactory() {
        this.includes = new LinkedHashSet<String>();
        this.endOfFileIncludes = new LinkedHashSet<String>();
    }


    public List<Update> createEndOfFileUpdates(CPPFile cppFile) throws Exception {
        if (!endOfFileIncludes.isEmpty()) {
            Update update = new InsertIncludeUpdate(endOfFileIncludes, cppFile, true);
            return Collections.singletonList(update);
        }
        return Collections.emptyList();
    }
    
    @Override
    public List<Update> createUpdates(CPPFile cppFile) throws Exception {
        if (!includes.isEmpty()) {
            Update update = new InsertIncludeUpdate(includes, cppFile, false);
            return Collections.singletonList(update);
        }
        return Collections.emptyList();
    }

    public void addIncludes(Collection<String> includes) {
        this.includes.addAll(includes);
    }

    public void addEndOfFileIncludes(Collection<String> includes) {
        this.endOfFileIncludes.addAll(includes);
    }

    public void clear() {
        this.includes.clear();
        this.endOfFileIncludes.clear();
    }
}

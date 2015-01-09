package jcpp.parser.cpp.update;

import java.util.Set;

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
        for (String include : includes) {
            sb.append("#include \"").append(include).append("\"").append(System.lineSeparator());
        }
        int insertOffset = computeOffset(cppFile, atEndOfFile);
        updatesResult.insert(insertOffset, sb.toString()); //TODO: includes are inserted at top of .h file before the #ifdef multiple inclusion guard
    }

    private static int computeOffset(CPPFile cppFile, boolean atEndOfFile) {
        if (atEndOfFile) {
            return cppFile.getTranslationUnit().getFileLocation().getNodeLength();
        }
        return 0;
    }
}

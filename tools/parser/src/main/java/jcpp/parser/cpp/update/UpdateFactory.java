package jcpp.parser.cpp.update;

import java.util.List;

import jcpp.parser.cpp.CPPFile;


public abstract class UpdateFactory {

    public UpdateFactory() {
    }


    public abstract List<Update> createUpdates(CPPFile cppFile) throws Exception;
}

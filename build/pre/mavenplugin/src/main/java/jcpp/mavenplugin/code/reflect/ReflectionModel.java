package jcpp.mavenplugin.code.reflect;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;


public class ReflectionModel {

    private Set<String> includes;

    private List<ClassModel> classes;

    private Set<String> usingNamespaceDeclarations;


    public ReflectionModel() {
        includes = new HashSet<String>();
        classes = new ArrayList<ClassModel>();
        usingNamespaceDeclarations = new HashSet<String>();
    }


    public List<ClassModel> getClasses() {
        return classes;
    }

    public void setClasses(List<ClassModel> classes) {
        this.classes = classes;
    }

    public void addClass(ClassModel clazz) {
        classes.add(clazz);
    }

    public Set<String> getIncludes() {
        return includes;
    }

    public void setIncludes(Set<String> includes) {
        this.includes = includes;
    }

    public void addInclude(String include) {
        includes.add(include);
    }

    public Set<String> getUsingNamespaceDeclarations() {
        return usingNamespaceDeclarations;
    }

    public void setUsingNamespaceDeclarations(Set<String> usingNamespaceDeclarations) {
        this.usingNamespaceDeclarations = usingNamespaceDeclarations;
    }

}

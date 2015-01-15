package jcpp.mavenplugin.code.reflect;

import java.util.ArrayList;
import java.util.List;


public class ClassModel {

    private String simpleName;
    private String className;
    private String annotatedSimpleName;
    private String annotatedCanonicalName;
    private List<String> namespaces;

    private String superClass;

    private boolean interfaceClass;
    private List<String> interfaces;

    private Long serialVersionUID;

    private List<FieldModel> fields;
    private List<MethodModel> constructors;
    private List<MethodModel> methods;

    private List<String> declaredClasses;
    private boolean abstractClass;
    private String declaringClass;
    private boolean primitive;

    private boolean enumClass;
    private List<String> enumConstants;


    public ClassModel(String simpleName) {
        this.simpleName = simpleName;
        namespaces = new ArrayList<String>();
        fields = new ArrayList<FieldModel>();
        constructors = new ArrayList<MethodModel>();
        methods = new ArrayList<MethodModel>();
        interfaces = new ArrayList<String>();
        declaredClasses = new ArrayList<String>();
        enumConstants = new ArrayList<String>();
    }


    public List<MethodModel> getMethods() {
        return methods;
    }

    public void setMethods(List<MethodModel> methods) {
        this.methods = methods;
    }

    public void addMethod(MethodModel method) {
        methods.add(method);
    }

    public List<MethodModel> getConstructors() {
        return constructors;
    }

    public void setConstructors(List<MethodModel> constructors) {
        this.constructors = constructors;
    }

    public void addConstructor(MethodModel method) {
        constructors.add(method);
    }

    public List<FieldModel> getFields() {
        return fields;
    }

    public void setFields(List<FieldModel> fields) {
        this.fields = fields;
    }

    public void addField(FieldModel field) {
        fields.add(field);
    }

    public long getSerialVersionUID() {
        return (serialVersionUID == null) ? 0L : serialVersionUID;
    }

    public void setSerialVersionUID(long serialVersionUID) {
        this.serialVersionUID = Long.valueOf(serialVersionUID);
    }

    public boolean isSerialVersionUIDFound() {
        return serialVersionUID != null;
    }

    public List<String> getNamespaces() {
        return namespaces;
    }

    public void setNamespaces(List<String> namespaces) {
        this.namespaces = namespaces;
    }

    public void addNamespaces(String nspace) {
        this.namespaces.add(nspace);
    }

    public String getSimpleName() {
        return simpleName;
    }

    public void setSimpleName(String simpleName) {
        this.simpleName = simpleName;
    }

    public String getSuperClass() {
        return superClass;
    }

    public void setSuperClass(String superClass) {
        this.superClass = superClass;
    }

    public boolean isHasSuperClass() {
        return superClass != null;
    }

    public List<String> getInterfaces() {
        return interfaces;
    }

    public void setInterfaces(List<String> interfaces) {
        this.interfaces = interfaces;
    }

    public void addInterface(String interfaze) {
        interfaces.add(interfaze);
    }

    public List<String> getDeclaredClasses() {
        return declaredClasses;
    }

    public void setDeclaredClasses(List<String> declaredClasses) {
        this.declaredClasses = declaredClasses;
    }

    public void addDeclaredClass(String declaredClass) {
        declaredClasses.add(declaredClass);
    }

    public String getAnnotatedSimpleName() {
        return annotatedSimpleName;
    }

    public void setAnnotatedSimpleName(String annotatedSimpleName) {
        this.annotatedSimpleName = annotatedSimpleName;
    }

    public String getAnnotatedCanonicalName() {
        return annotatedCanonicalName;
    }

    public void setAnnotatedCanonicalName(String annotatedCanonicalName) {
        this.annotatedCanonicalName = annotatedCanonicalName;
    }

    public String getClassName() {
        return className;
    }

    public void setClassName(String className) {
        this.className = className;
    }

    public boolean isAbstractClass() {
        return abstractClass;
    }

    public void setAbstractClass(boolean abstractClass) {
        this.abstractClass = abstractClass;
    }

    public String getDeclaringClass() {
        return declaringClass;
    }

    public void setDeclaringClass(String declaringClass) {
        this.declaringClass = declaringClass;
    }

    public boolean isHasDeclaringClass() {
        return declaringClass != null;
    }

    public boolean isPrimitive() {
        return primitive;
    }

    public void setPrimitive(boolean primitive) {
        this.primitive = primitive;
    }

    public boolean isEnumClass() {
        return enumClass;
    }

    public void setEnumClass(boolean enumClass) {
        this.enumClass = enumClass;
    }

    public List<String> getEnumConstants() {
        return enumConstants;
    }

    public void setEnumConstants(List<String> enumConstants) {
        this.enumConstants = enumConstants;
    }

    public void addEnumConstant(String enumConstant) {
        enumConstants.add(enumConstant);
    }

    public boolean isInterfaceClass() {
        return interfaceClass;
    }

    public void setInterfaceClass(boolean interfaceClass) {
        this.interfaceClass = interfaceClass;
    }

}

package jcpp.mavenplugin.code.reflect;

import java.util.ArrayList;
import java.util.List;

import jcpp.mavenplugin.code.Utils;


public class MethodModel {

    private String name;
    private int index;
    private String returnType;
    private boolean staticMethod;
    private boolean publicMethod;
    private boolean privateMethod;
    private boolean protectedMethod;

    private List<ParameterModel> parameters;


    public MethodModel(String name, String returnType) {
        this.name = name;
        this.returnType = returnType;
        this.parameters = new ArrayList<ParameterModel>();
    }


    public boolean isVoidReturnType() {
        return Utils.getTypeClass(returnType) == Utils.J_PRIMITIVE_VOID;
    }

    public boolean isPrimitiveReturnType() {
        return Utils.isPrimitive(returnType);
    }

    public String getReturnTypeClass() {
        return Utils.getTypeClass(returnType);
    }

    public boolean getProtectedMethod() {
        return protectedMethod;
    }

    public void setProtectedMethod(boolean protectedMethod) {
        this.protectedMethod = protectedMethod;
    }

    public boolean getPrivateMethod() {
        return privateMethod;
    }

    public void setPrivateMethod(boolean privateMethod) {
        this.privateMethod = privateMethod;
    }

    public boolean getPublicMethod() {
        return publicMethod;
    }

    public void setPublicMethod(boolean isPublic) {
        this.publicMethod = isPublic;
    }

    public boolean getStaticMethod() {
        return staticMethod;
    }

    public void setStaticMethod(boolean isStatic) {
        this.staticMethod = isStatic;
    }

    public List<ParameterModel> getParameters() {
        return parameters;
    }

    public void setParameters(List<ParameterModel> parameters) {
        this.parameters = parameters;
    }

    public void addParameters(ParameterModel param) {
        parameters.add(param);
    }

    public int getArgCount() {
        return parameters.size();
    }

    public String getReturnType() {
        return returnType;
    }

    public void setReturnType(String returnType) {
        this.returnType = returnType;
    }

    public String getModifiedName() {
        String modifiedName = name.replace("~", "Destructor");
        if (index > 0) {
            modifiedName += "_" + index;
        }
        return modifiedName;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getIndex() {
        return index;
    }

    public void setIndex(int index) {
        this.index = index;
    }

}

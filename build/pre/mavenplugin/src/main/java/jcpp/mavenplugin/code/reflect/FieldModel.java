package jcpp.mavenplugin.code.reflect;

import jcpp.mavenplugin.code.Utils;


public class FieldModel {
    private String type;
    private String name;
    private boolean staticField;
    private boolean constField;
    private boolean publicField;
    private boolean privateField;
    private boolean protectedField;


    public FieldModel(String type, String name) {
        this.type = type;
        this.name = name;
    }


    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public String getTypeClass() {
        return Utils.getTypeClass(type);
    }

    public boolean getStaticField() {
        return staticField;
    }

    public void setStaticField(boolean staticField) {
        this.staticField = staticField;
    }

    public boolean getPublicField() {
        return publicField;
    }

    public void setPublicField(boolean publicField) {
        this.publicField = publicField;
    }

    public boolean getPrivateField() {
        return privateField;
    }

    public void setPrivateField(boolean privateField) {
        this.privateField = privateField;
    }

    public boolean getProtectedField() {
        return protectedField;
    }

    public void setProtectedField(boolean protectedField) {
        this.protectedField = protectedField;
    }

    public boolean isPrimitive() {
        return Utils.isPrimitive(type);
    }

    public boolean isConstField() {
        return constField;
    }

    public void setConstField(boolean constField) {
        this.constField = constField;
    }
}

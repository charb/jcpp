package jcpp.mavenplugin.code.reflect;

import jcpp.mavenplugin.code.Utils;


public class ParameterModel {
    private String name;
    private String type;


    public ParameterModel(String name, String type) {
        this.name = name;
        setType(type);
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

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public boolean isPrimitive() {
        return Utils.isPrimitive(type);
    }

}

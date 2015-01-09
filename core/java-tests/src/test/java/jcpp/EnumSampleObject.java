package jcpp;

import java.io.*;

public enum EnumSampleObject{	
    ENUM1("Enum1",1),
    ENUM2("Enum2",2),
    ENUM3("Enum3",3),
    ENUM4("Enum4",4),
    ENUM5("Enum5",5);
    private String strField;
    private int iField;

    EnumSampleObject(String fieldString,int i){
        this.strField=fieldString;
        iField=i;
    }

    public String getStringField(){
        return strField;
    }

    public int getIntField(){
        return iField;
    }
}

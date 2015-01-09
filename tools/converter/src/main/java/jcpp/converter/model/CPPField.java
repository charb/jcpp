package jcpp.converter.model;

import java.util.*;

public class CPPField{
    protected CPPClass clazz;
    protected String name;
    protected boolean bStatic;
    protected boolean bProtected;
    protected CPPType type;

	public CPPField(CPPClass clazz){
        this.clazz=clazz;
	}

    public CPPClass getClazz(){
        return clazz;
    }

    public String getName(){
        return name;
    }

    public void setName(String n){
        name=n;
    }

    public boolean isStatic(){
        return bStatic;
    }

    public void setStatic(boolean s){
        bStatic=s;
    }

    public boolean isProtected(){
        return bProtected;
    }

    public void setProtected(boolean b){
        bProtected=b;
    }

    public CPPType getType(){
        return type;
    }

    public void setType(CPPType n){
        type=n;
    }
}
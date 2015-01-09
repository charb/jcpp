package jcpp.converter.model;

import java.util.*;
import jcpp.converter.model.stmt.*;

public class CPPMethod{
    protected CPPClass clazz;
    protected CPPMethodInfo info;
    protected CPPBlockStatement body;

	public CPPMethod(CPPClass clazz){
        this.clazz=clazz;
	}

    public CPPClass getClazz(){
        return clazz;
    }

    public CPPMethodInfo getInfo(){
        return info;
    }

    public void setInfo(CPPMethodInfo info){
        this.info=info;
    }

    public CPPBlockStatement getBody(){
        return body;
    }

    public void setBody(CPPBlockStatement b){
        body=b;
    }

    public String getSignature(){
        return info.getSignature();
    }

    public String toString(){
        return info.toString();
    }
}
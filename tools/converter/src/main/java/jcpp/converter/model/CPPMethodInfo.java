package jcpp.converter.model;

import java.util.*;

public class CPPMethodInfo{
    protected CPPClass clazz;
    protected String name;
    protected int lineNumber;
    protected String signature;
    protected boolean bConstructor;
    protected boolean bStatic;
    protected boolean bProtected;
    protected boolean bAbstract;
    protected CPPType returnType;
    protected List<CPPType> parameters;
    protected List<String> parameterNames;

	public CPPMethodInfo(CPPClass clazz){
        this.clazz=clazz;
        parameters=new ArrayList<CPPType>();
        parameterNames=new ArrayList<String>();
	}

    public CPPClass getClazz(){
        return clazz;
    }

    public int getLineNumber(){
        return lineNumber;
    }

    public void setLineNumber(int i){
        lineNumber=i;
    }

    public String getName(){
        return name;
    }

    public void setName(String n){
        name=n;
    }

    public String getSignature(){
        return signature;
    }

    public void setSignature(String n){
        signature=n;
    }

    public boolean isConstructor(){
        return bConstructor;
    }

    public void setConstructor(boolean s){
        bConstructor=s;
    }

    public boolean isAbstract(){
        return bAbstract;
    }

    public void setAbstract(boolean s){
        bAbstract=s;
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

    public CPPType getReturnType(){
        return returnType;
    }

    public void setReturnType(CPPType n){
        if (n!=null){
            returnType=n;
        }
    }

    public List<CPPType> getParameters(){
        return parameters;
    }

    public void addParameter(CPPType t){
        parameters.add(t);
    }

    public List<String> getParameterNames(){
        return parameterNames;
    }

    public void addParameterName(String t){
        parameterNames.add(t);
    }

    public String toString(){
        return "[Name:"+name+",Line:"+lineNumber+"]";
    }
}
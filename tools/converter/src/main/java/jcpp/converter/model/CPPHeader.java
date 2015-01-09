package jcpp.converter.model;

import java.util.*;

public class CPPHeader{
    protected CPPClass cppClass;
    protected String cppFileName;
    protected String ifDefName;
    protected Map<CPPType,CPPType> includes;
    protected Map<CPPType,CPPType> usings;
    protected Map<Integer,CPPMethodInfo> methods;

	public CPPHeader(CPPClass cppClass){
        this.cppClass=cppClass;
        includes=new TreeMap<CPPType,CPPType>();
        usings=new TreeMap<CPPType,CPPType>();
        methods=new TreeMap<Integer,CPPMethodInfo>();
	}

    public String getCPPFileName(){
        return cppFileName;
    }

    public void setCPPFileName(String n){
        cppFileName=n;
    }

    public String getIfDefName(){
        return ifDefName;
    }

    public void setIfDefName(String n){
        ifDefName=n;
    }

	public void addDependency(CPPType type){
        if (type!=null && !type.equals(cppClass.getType()) && !type.isPrimitive()){
    		includes.put(type,type);
            if (type.getNamespaces().size()>0){
    		  usings.put(new CPPType(type,""),new CPPType(type,""));
            }
        }
	}

    public boolean isType(String n){
        for (CPPType t : includes.keySet()){
            if (t.getName().equals(n)){
                return true;
            }
        }
        return false;
    }

    public void setDependencies(){
        for (CPPMethodInfo i : methods.values()){
            if (i.getReturnType()!=null){
                addDependency(i.getReturnType());
            }
            for (CPPType t : i.getParameters()) {
                addDependency(t);
            }
        }
    }

	public Collection<CPPType> getIncludes(){
		return includes.values();
	}

	public Collection<CPPType> getUsings(){
		return usings.values();
	}

	public Map<Integer,CPPMethodInfo> getMethods(){
        return methods;
    }

    public CPPMethodInfo getMethod(Integer n){
        return methods.get(n);
    }

    public void addMethod(CPPMethodInfo f){
        methods.put(f.getLineNumber(),f);
    }
}
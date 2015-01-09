package jcpp.converter.model;

import java.util.*;

public class CPPSource{
    protected CPPClass cppClass;
    protected String cppFileName;
    protected Map<CPPType,CPPType> includes;
    protected Map<CPPType,CPPType> usings;
    protected Map<Integer,CPPMethod> methods;

	public CPPSource(CPPClass cppClass){
        this.cppClass=cppClass;
        includes=new TreeMap<CPPType,CPPType>();
        usings=new TreeMap<CPPType,CPPType>();
        methods=new TreeMap<Integer,CPPMethod>();
	}

	public String getCPPFileName(){
        return cppFileName;
    }

    public void setCPPFileName(String n){
        cppFileName=n;
    }

    public boolean isType(String n){
        for (CPPType t : includes.keySet()){
            if (t.getName().equals(n)){
                return true;
            }
        }
        return false;
    }

	public void addDependency(CPPType type){
        if (type!=null && !type.isPrimitive()) {
    		includes.put(type,type);
            if (type.getNamespaces().size()>0){
    	        usings.put(new CPPType(type,""),new CPPType(type,""));
            }
        }
	}

    public CPPType fixType(CPPType cppType){
        if (cppType.getNamespaces().size()==0){
            for (CPPType l : includes.keySet()){
                if (l.getName().equals(cppType.getName())){
                    return l;
                }
            }
            //TODO
            System.out.println("WARNING !!!!!!!!!!!!!!: couldn't fix type "+cppType+" current types "+includes.keySet());
        }
        return cppType;
    }

	public Collection<CPPType> getIncludes(){
		return includes.values();
	}

	public Collection<CPPType> getUsings(){
		return usings.values();
	}

	public Map<Integer,CPPMethod> getMethods(){
        return methods;
    }

    public CPPMethod getMethod(int s,int e){
        for (Integer i : methods.keySet()){
            if (i>=s && i<=e){
                return methods.get(i);
            }
        }
        System.out.println(methods);//TODO throw runtimeexce
        return null;
    }

    public void addMethod(CPPMethod f){
        methods.put(f.getInfo().getLineNumber(),f);
    }
}
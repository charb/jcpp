package jcpp.converter.model;

import java.util.*;

public class CPPClass{
    protected CPPPackage cppPackage;
    protected boolean bIsInterface;
    protected Map<String,CPPField> fields;
    protected CPPHeader header;
    protected CPPSource source;
    protected CPPType type;
    protected String javaClassName;
    protected String superJavaClassName;
    protected CPPType superClass;
    protected List<String> interfacesJavaClassName;
    protected List<CPPType> interfaces;

	public CPPClass(CPPPackage cppPackage){
        this.cppPackage=cppPackage;
        type=new CPPType();
        type.setType(CPPType.Type.OBJECT);
        fields=new TreeMap<String,CPPField>();
        header=new CPPHeader(this);
        source=new CPPSource(this);
        interfacesJavaClassName=new ArrayList<String>();
        interfaces=new ArrayList<CPPType>();
	}

    public CPPType getType(){
        return type;
    }

    public List<String> getNamespaces(){
        return type.getNamespaces();
    }

    public String getName(){
        return type.getName();
    }

    public void setName(String n){
        type.setName(n);
    }

    public boolean isInterface(){
        return bIsInterface;
    }

    public void setIsInterface(boolean b){
        bIsInterface=b;
    }

    public String getJavaClassName(){
        return javaClassName;
    }

    public void setJavaClassName(String n){
        javaClassName=n;
    }

    public String getSuperJavaClassName(){
        return superJavaClassName;
    }

    public void setSuperJavaClassName(String n){
        superJavaClassName=n;
    }

	public CPPPackage getPackage(){
        return cppPackage;
    }

    public void setPackage(CPPPackage n){
        cppPackage=n;
    }    

    public Map<String,CPPField> getFields(){
        return fields;
    }

    public CPPField getField(String n){
        return fields.get(n);
    }

    public void addField(CPPField f){
        fields.put(f.getName(),f);
    }

    public CPPType getSuperClass(){
        return superClass;
    }

    public void setSuperClass(CPPType t){
        superClass=t;
    }

    public List<CPPType> getInterfaces(){
        return interfaces;
    }

    public void addInterface(CPPType t){
        interfaces.add(t);
    }

    public List<String> getInterfacesJavaClassName(){
        return interfacesJavaClassName;
    }

    public void addInterfaceJavaClassName(String s){
        interfacesJavaClassName.add(s);
    }

    public CPPHeader getHeader(){
        return header;
    }

    public CPPSource getSource(){
        return source;
    }

    public boolean isType(String n){
        if (superClass.getName().equals(n)){
            return true;
        }
        for (CPPType t : interfaces){
            if (t.getName().equals(n)){
                return true;
            }
        }
        if (header.isType(n)){
            return true;
        }
        if (source.isType(n)){
            return true;
        }
        return false;
    }

    public void setDependencies(){
        setHeaderDependencies();
        setSourceDependencies();
    }

    public void setHeaderDependencies(){
        for (CPPField f : fields.values()){
            header.addDependency(f.getType());
        }
        for (CPPType t : interfaces){
            header.addDependency(t);
        }
        if (superClass!=null){
            header.addDependency(superClass);
        }
        header.setDependencies();
    }

    public void setSourceDependencies(){
        source.addDependency(getType());
    }
}
package jcpp.converter.model;

import java.util.*;

public class CPPPackage extends CPPClass{
    protected String cppFolderName;
    protected String javaPackageName;
	protected CPPPackage parent;
    protected List<CPPPackage> subPackages;
    protected List<CPPClass> classes;

	public CPPPackage(){
        super(null);
		subPackages=new ArrayList<CPPPackage>();
		classes=new ArrayList<CPPClass>();
        header=new CPPPackageHeader(this);
        source=new CPPPackageSource(this);
	}

    public String getCPPFolderName(){
        return cppFolderName;
    }

    public void setCPPFolderName(String n){
        cppFolderName=n;
    }

    public String getJavaPackageName(){
        return javaPackageName;
    }

    public void setJavaPackageName(String n){
        javaPackageName=n;
    }

    public CPPPackage getParent(){
        return parent;
    }

    public void setDependencies(){
        super.setDependencies();
        if (parent!=null){
            source.addDependency(parent.getType());
        }
        for (CPPPackage sp : subPackages){        
            source.addDependency(sp.getType());
        }
        for (CPPClass c : classes){
            source.addDependency(c.getType());
        }
    }

    public void setParent(CPPPackage p){
        parent=p;
        p.addSubPackage(this);
    }

    public List<CPPPackage> getSubPackages(){
        return subPackages;
    }

    public void addSubPackage(CPPPackage p){
        subPackages.add(p);
    }

    public List<CPPClass> getClasses(){
        return classes;
    }

    public void addClass(CPPClass c){
        classes.add(c);
    }

    public CPPPackageHeader getHeader(){
        return (CPPPackageHeader)header;
    }

    public CPPPackageSource getSource(){
        return (CPPPackageSource)source;
    }
}
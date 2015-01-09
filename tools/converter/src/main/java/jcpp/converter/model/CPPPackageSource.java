package jcpp.converter.model;

import java.util.*;

public class CPPPackageSource extends CPPSource{
    protected CPPPackage cppPackage;
    
    public CPPPackageSource(CPPPackage cppPackage){
    	super(cppPackage);
        this.cppPackage=cppPackage;
	}
}
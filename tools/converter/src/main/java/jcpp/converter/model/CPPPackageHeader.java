package jcpp.converter.model;

import java.util.*;

public class CPPPackageHeader extends CPPHeader{
    protected CPPPackage cppPackage;

	public CPPPackageHeader(CPPPackage cppPackage){
		super(cppPackage);
        this.cppPackage=cppPackage;
	}
}
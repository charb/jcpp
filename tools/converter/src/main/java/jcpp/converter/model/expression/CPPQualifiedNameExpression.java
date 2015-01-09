package jcpp.converter.model.expression;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.stmt.*;

//used for A.B in static imports
public class CPPQualifiedNameExpression extends CPPNameExpression{
    protected CPPNameExpression qualifier;

	public CPPQualifiedNameExpression(CPPMethod method){
        super(method);
	}

    public CPPNameExpression getQualifier(){
        return qualifier;
    }

    public void setQualifier(CPPNameExpression n){
        this.qualifier=n;
    }
}
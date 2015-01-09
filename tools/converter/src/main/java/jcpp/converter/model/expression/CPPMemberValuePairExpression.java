package jcpp.converter.model.expression;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.stmt.*;

public class CPPMemberValuePairExpression extends CPPExpression{
    protected String name;
    protected CPPExpression value;

	public CPPMemberValuePairExpression(CPPMethod method){
        super(method);
	}

    public String getName(){
        return name;
    }

    public void setName(String e){
        name=e;
    }

    public CPPExpression getValue(){
        return value;
    }

    public void setValue(CPPExpression e){
        value=e;
    }
}
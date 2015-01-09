package jcpp.converter.model.stmt;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.expression.*;

public class CPPDoStatement extends CPPStatement{
    protected CPPStatement body;
    protected CPPExpression condition;

	public CPPDoStatement(CPPMethod method){
        super(method);
	}

    public CPPStatement getBody(){
        return body;
    }

    public void setBody(CPPStatement body){
    	this.body=body;
    }

    public CPPExpression getCondition(){
        return condition;
    }

    public void setCondition(CPPExpression m){
        this.condition=m;
    }
}
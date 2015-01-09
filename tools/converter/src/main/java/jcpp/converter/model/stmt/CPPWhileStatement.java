package jcpp.converter.model.stmt;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.expression.*;

public class CPPWhileStatement extends CPPStatement{
    protected CPPExpression condition;
    protected CPPStatement body;

	public CPPWhileStatement(CPPMethod method){
        super(method);
	}

    public CPPExpression getCondition(){
        return condition;
    }

    public void setCondition(CPPExpression m){
        this.condition=m;
    }

    public CPPStatement getBody(){
        return body;
    }

    public void setBody(CPPStatement s){
        this.body=s;
    }
}
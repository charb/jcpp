package jcpp.converter.model.expression;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.stmt.*;

public class CPPConditionalExpression extends CPPExpression{
    protected CPPExpression condition;
    protected CPPExpression elseExpression;
    protected CPPExpression thenExpression;

	public CPPConditionalExpression(CPPMethod method){
        super(method);
	}

    public CPPExpression getCondition(){
        return condition;
    }

    public void setCondition(CPPExpression i){
    	condition=i;
    }

    public CPPExpression getElseExpression(){
        return elseExpression;
    }

    public void setElseExpression(CPPExpression i){
    	elseExpression=i;
    }

    public CPPExpression getThenExpression(){
        return thenExpression;
    }

    public void setThenExpression(CPPExpression i){
        thenExpression=i;
    }
}
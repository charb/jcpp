package jcpp.converter.model.expression;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.stmt.*;

public class CPPCastExpression extends CPPExpression{
    protected CPPExpression expression;
    protected CPPType type;

	public CPPCastExpression(CPPMethod method){
        super(method);
	}

    public CPPExpression getExpression(){
        return expression;
    }

    public void setExpression(CPPExpression i){
    	expression=i;
    }

    public CPPType getType(){
        return type;
    }

    public void setType(CPPType i){
    	type=i;
    }
}
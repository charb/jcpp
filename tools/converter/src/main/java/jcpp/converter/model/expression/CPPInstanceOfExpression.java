package jcpp.converter.model.expression;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.stmt.*;

public class CPPInstanceOfExpression extends CPPExpression{
    protected CPPType type;
    protected CPPExpression expression;

	public CPPInstanceOfExpression(CPPMethod method){
        super(method);
	}

    public CPPType getType(){
        return type;
    }

    public void setType(CPPType e){
        type=e;
    }

    public CPPExpression getExpression(){
        return expression;
    }

    public void setExpression(CPPExpression e){
        expression=e;
    }
}
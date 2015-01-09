package jcpp.converter.model.stmt;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.expression.*;

public class CPPExpressionStatement extends CPPStatement{
    protected CPPExpression expression;

	public CPPExpressionStatement(CPPMethod method){
        super(method);
	}

    public CPPExpression getExpression(){
        return expression;
    }

    public void setExpression(CPPExpression m){
        this.expression=m;
    }
}
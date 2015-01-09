package jcpp.converter.model.expression;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.stmt.*;

//classExpression is the scope and can be null
public class CPPSuperExpression extends CPPExpression{
    protected CPPExpression classExpression;

	public CPPSuperExpression(CPPMethod method){
        super(method);
	}

    public CPPExpression getClassExpression(){
        return classExpression;
    }

    public void setClassExpression(CPPExpression e){
        classExpression=e;
    }
}
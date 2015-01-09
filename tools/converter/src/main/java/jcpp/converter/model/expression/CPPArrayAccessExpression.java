package jcpp.converter.model.expression;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.stmt.*;

//TODO should be name->getXXX(index) with/out dynamic_cast ?
public class CPPArrayAccessExpression extends CPPExpression{
    protected CPPExpression index;
    protected CPPExpression name;

	public CPPArrayAccessExpression(CPPMethod method){
        super(method);
	}

    public CPPExpression getIndex(){
        return index;
    }

    public void setIndex(CPPExpression i){
    	index=i;
    }

    public CPPExpression getName(){
        return name;
    }

    public void setName(CPPExpression i){
    	name=i;
    }
}
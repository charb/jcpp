package jcpp.converter.model.expression;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.stmt.*;

public class CPPClassExpression extends CPPExpression{
    protected CPPType type;

	public CPPClassExpression(CPPMethod method){
        super(method);
	}

    public CPPType getType(){
        return type;
    }

    public void setType(CPPType i){
    	type=i;
    }
}
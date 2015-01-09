package jcpp.converter.model.expression;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.stmt.*;

//classExpression which is the scope should always be null!
public class CPPThisExpression extends CPPExpression{
    protected CPPExpression classExpression;

	public CPPThisExpression(CPPMethod method){
        super(method);
	}

    public CPPExpression getClassExpression(){
        return classExpression;
    }

    public void setClassExpression(CPPExpression e){
        classExpression=e;
    }
}
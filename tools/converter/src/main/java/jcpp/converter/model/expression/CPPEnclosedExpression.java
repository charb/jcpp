package jcpp.converter.model.expression;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.stmt.*;

//simply represents "{expr}"
public class CPPEnclosedExpression extends CPPExpression{
    protected CPPExpression inner;

	public CPPEnclosedExpression(CPPMethod method){
        super(method);
	}

    public CPPExpression getInner(){
        return inner;
    }

    public void setInner(CPPExpression i){
    	inner=i;
    }
}
package jcpp.converter.model.expression;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.stmt.*;

//TODO used only in array creation?
public class CPPArrayInitializerExpression extends CPPExpression{
    protected List<CPPExpression> values;

	public CPPArrayInitializerExpression(CPPMethod method){
        super(method);
        values=new ArrayList<CPPExpression>();
	}

    public List<CPPExpression> getValues(){
        return values;
    }

    public void addValue(CPPExpression e){
        values.add(e);
    }
}
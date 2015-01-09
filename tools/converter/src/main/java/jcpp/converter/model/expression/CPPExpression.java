package jcpp.converter.model.expression;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.stmt.*;

public class CPPExpression{
    protected CPPMethod method;

	public CPPExpression(CPPMethod method){
        this.method=method;
	}

    public CPPMethod getMethod(){
        return method;
    }
}
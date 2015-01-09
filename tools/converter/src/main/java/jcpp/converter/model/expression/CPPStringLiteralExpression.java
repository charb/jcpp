package jcpp.converter.model.expression;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.stmt.*;

public class CPPStringLiteralExpression extends CPPLiteralExpression{
    protected String value;

	public CPPStringLiteralExpression(CPPMethod method){
        super(method);
	}

    public String getValue(){
        return value;
    }

    public void setValue(String e){
        value=e;
    }
}
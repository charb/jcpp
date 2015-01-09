package jcpp.converter.model.expression;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.stmt.*;

public class CPPNameExpression extends CPPExpression{
    protected String name;

	public CPPNameExpression(CPPMethod method){
        super(method);
	}

    public String getName(){
        return name;
    }

    public void setName(String name){
        this.name=name;
    }
}
package jcpp.converter.model.stmt;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.expression.*;

public class CPPLabeledStatement extends CPPStatement{
    protected String label;
    protected CPPStatement statement;

	public CPPLabeledStatement(CPPMethod method){
        super(method);
	}

    public String getLabel(){
        return label;
    }

    public void setLabel(String s){
        this.label=s;
    }

    public CPPStatement getStatement(){
        return statement;
    }

    public void setStatement(CPPStatement s){
        this.statement=s;
    }
}
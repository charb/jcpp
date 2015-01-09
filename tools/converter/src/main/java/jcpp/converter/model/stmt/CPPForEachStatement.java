package jcpp.converter.model.stmt;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.expression.*;

public class CPPForEachStatement extends CPPStatement{
    protected CPPStatement body;
    protected CPPExpression iterable;
    protected CPPVariableDeclarationExpression variable;

	public CPPForEachStatement(CPPMethod method){
        super(method);
	}

    public CPPStatement getBody(){
        return body;
    }

    public void setBody(CPPStatement body){
    	this.body=body;
    }

    public CPPExpression getIterable(){
        return iterable;
    }

    public void setIterable(CPPExpression m){
        this.iterable=m;
    }

    public CPPVariableDeclarationExpression getVariable(){
        return variable;
    }

    public void setVariable(CPPVariableDeclarationExpression e){
        this.variable=e;
    }
}
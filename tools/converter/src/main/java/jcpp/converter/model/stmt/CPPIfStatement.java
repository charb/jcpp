package jcpp.converter.model.stmt;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.expression.*;

public class CPPIfStatement extends CPPStatement{
    protected CPPExpression condition;
    protected CPPStatement elseStmt;
    protected CPPStatement thenStmt;

	public CPPIfStatement(CPPMethod method){
        super(method);
	}

    public CPPExpression getCondition(){
        return condition;
    }

    public void setCondition(CPPExpression m){
        this.condition=m;
    }

    public CPPStatement getElseStatement(){
        return elseStmt;
    }

    public void setElseStatement(CPPStatement s){
        this.elseStmt=s;
    }

    public CPPStatement getThenStatement(){
        return thenStmt;
    }

    public void setThenStatement(CPPStatement s){
        this.thenStmt=s;
    }
}
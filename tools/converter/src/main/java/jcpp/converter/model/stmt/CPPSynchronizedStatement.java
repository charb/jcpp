package jcpp.converter.model.stmt;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.expression.*;

public class CPPSynchronizedStatement extends CPPStatement{
    protected CPPBlockStatement blockStatement;
    protected CPPExpression expression;

	public CPPSynchronizedStatement(CPPMethod method){
        super(method);
	}

    public CPPExpression getExpression(){
        return expression;
    }

    public void setExpression(CPPExpression m){
        this.expression=m;
    }

    public CPPBlockStatement getBlockStatement(){
        return blockStatement;
    }

    public void setBlockStatement(CPPBlockStatement s){
        this.blockStatement=s;
    }
}
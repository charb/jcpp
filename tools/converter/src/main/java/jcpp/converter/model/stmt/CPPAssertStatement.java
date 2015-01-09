package jcpp.converter.model.stmt;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.expression.*;

public class CPPAssertStatement extends CPPStatement{
    protected CPPExpression check;
    protected CPPExpression message;

	public CPPAssertStatement(CPPMethod method){
        super(method);
	}

    public CPPExpression getCheck(){
        return check;
    }

    public void setCheck(CPPExpression check){
    	this.check=check;
    }

    public CPPExpression getMessage(){
        return message;
    }

    public void setMessage(CPPExpression m){
        this.message=m;
    }
}
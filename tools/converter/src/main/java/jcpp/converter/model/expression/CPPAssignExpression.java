package jcpp.converter.model.expression;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.stmt.*;

public class CPPAssignExpression extends CPPExpression{
    public enum Operator{
        and("&="), assign("="), 
        lShift("<<="), minus("-=") ,
        or("|=") ,plus("+=") ,
        rem("%="), rSignedShift(">>=") ,
        rUnsignedShift(">>>=") ,
        slash("/=") ,star("*=") ,
        xor("^=");
        
        protected String s;

        Operator(String s){
            this.s=s;
        }

        public String toString(){
            return s;
        }
    }

    protected Operator operator;
    protected CPPExpression target;
    protected CPPExpression value;

	public CPPAssignExpression(CPPMethod method){
        super(method);
	}

    public CPPExpression getTarget(){
        return target;
    }

    public void setTarget(CPPExpression i){
    	target=i;
    }

    public CPPExpression getValue(){
        return value;
    }

    public void setValue(CPPExpression i){
    	value=i;
    }

    public Operator getOperator(){
        return operator;
    }

    public void setOperator(Operator i){
        operator=i;
    }
}
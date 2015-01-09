package jcpp.converter.model.expression;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.stmt.*;

public class CPPBinaryExpression extends CPPExpression{
    public enum Operator{
        and("&&") ,binAnd("&"),
        binOr("|"),divide("/") ,
        equals("==") ,greater(">") ,
        greaterEquals(">=") ,less("<") ,
        lessEquals("<=") ,lShift("<<") ,
        minus("-") ,notEquals("!=") ,
        or("||") ,plus("+") ,
        remainder("%") ,rSignedShift(">>") ,
        rUnsignedShift(">>>") ,times("*") ,xor("^");

        protected String s;

        Operator(String s){
            this.s=s;
        }

        public String toString(){
            return s;
        }
    }
    protected Operator operator;
    protected CPPExpression left;
    protected CPPExpression right;

	public CPPBinaryExpression(CPPMethod method){
        super(method);
	}

    public CPPExpression getLeft(){
        return left;
    }

    public void setLeft(CPPExpression i){
    	left=i;
    }

    public CPPExpression getRight(){
        return right;
    }

    public void setRight(CPPExpression i){
    	right=i;
    }

    public Operator getOperator(){
        return operator;
    }

    public void setOperator(Operator i){
        operator=i;
    }
}
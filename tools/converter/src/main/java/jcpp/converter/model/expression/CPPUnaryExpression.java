package jcpp.converter.model.expression;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.stmt.*;

public class CPPUnaryExpression extends CPPExpression{
    public enum Operator{
        inverse("~",true) ,negative("-",true) ,
        not("!",true) ,posDecrement("--",false) ,
        posIncrement("++",false) ,positive("+",true) ,
        preDecrement("--",true), preIncrement("++",true);
        protected String s;
        protected boolean left;

        Operator(String s,boolean left){
            this.s=s;
            this.left=left;
        }

        public boolean isLeft(){
            return left;
        }

        public String toString(){
            return s;
        }
    };
    protected CPPExpression expression;
    protected Operator operator;

	public CPPUnaryExpression(CPPMethod method){
        super(method);
	}

    public CPPExpression getExpression(){
        return expression;
    }

    public void setExpression(CPPExpression e){
        expression=e;
    }

    public Operator getOperator(){
        return operator;
    }

    public void setOperator(Operator o){
        operator=o;
    }
}
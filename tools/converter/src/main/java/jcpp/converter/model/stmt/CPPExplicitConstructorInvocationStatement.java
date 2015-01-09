package jcpp.converter.model.stmt;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.expression.*;

//TODO this represents this|super(p0,p1,p2,...) in the constructor
public class CPPExplicitConstructorInvocationStatement extends CPPStatement{
    protected CPPExpression expression;
    protected List<CPPExpression> args;
    protected List<CPPType> typeArgs;
    protected boolean bIsThis;

	public CPPExplicitConstructorInvocationStatement(CPPMethod method){
        super(method);
        args=new ArrayList<CPPExpression>();
        typeArgs=new ArrayList<CPPType>();
	}

    public CPPExpression getExpression(){
        return expression;
    }

    public void setExpression(CPPExpression m){
        this.expression=m;
    }

    public List<CPPExpression> getArgs(){
        return args;
    }

    public void addArg(CPPExpression e){
        args.add(e);
    }

    public List<CPPType> getTypeArgs(){
        return typeArgs;
    }

    public void addTypeArg(CPPType e){
        typeArgs.add(e);
    }

    public boolean isThis(){
        return bIsThis;
    }

    public void setIsThis(boolean b){
        bIsThis=b;
    }
}
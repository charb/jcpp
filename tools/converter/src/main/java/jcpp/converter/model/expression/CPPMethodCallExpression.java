package jcpp.converter.model.expression;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.stmt.*;

public class CPPMethodCallExpression extends CPPExpression{
    protected String name;
    protected List<CPPExpression> args;
    protected CPPNameExpression nameExpression;
    protected CPPExpression scope;
    protected List<CPPType> typeArgs;

	public CPPMethodCallExpression(CPPMethod method){
        super(method);
        args=new ArrayList<CPPExpression>();
        typeArgs=new ArrayList<CPPType>();
	}

    public String getName(){
        return name;
    }

    public void setName(String name){
        this.name=name;
    }

    public List<CPPExpression> getArgs(){
        return args;
    }

    public void addArg(CPPExpression e){
        args.add(e);
    }

    public CPPNameExpression getNameExpression(){
        return nameExpression;
    }

    public void setNameExpression(CPPNameExpression n){
        this.nameExpression=n;
    }

    public CPPExpression getScope(){
        return scope;
    }

    public void setScope(CPPExpression n){
        this.scope=n;
    }

    public List<CPPType> getTypeArgs(){
        return typeArgs;
    }

    public void addTypeArg(CPPType e){
        typeArgs.add(e);
    }
}
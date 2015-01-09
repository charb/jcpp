package jcpp.converter.model.stmt;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.expression.*;

public class CPPForStatement extends CPPStatement{
    protected CPPStatement body;
    protected CPPExpression compare;
    protected List<CPPExpression> init;
    protected List<CPPExpression> update;

	public CPPForStatement(CPPMethod method){
        super(method);
        init=new ArrayList<CPPExpression>();
        update=new ArrayList<CPPExpression>();
	}

    public CPPStatement getBody(){
        return body;
    }

    public void setBody(CPPStatement body){
    	this.body=body;
    }

    public CPPExpression getCompare(){
        return compare;
    }

    public void setCompare(CPPExpression m){
        this.compare=m;
    }

    public List<CPPExpression> getInit(){
        return init;
    }

    public void addInit(CPPExpression e){
        init.add(e);
    }

    public List<CPPExpression> getUpdate(){
        return update;
    }

    public void addUpdate(CPPExpression e){
        update.add(e);
    }
}
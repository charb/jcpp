package jcpp.converter.model.stmt;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.expression.*;

public class CPPTryStatement extends CPPStatement{
    protected List<CPPCatchClauseStatement> catchs;
    protected CPPBlockStatement finallyBlock;
    protected CPPBlockStatement tryBlock;
    protected List<CPPVariableDeclarationExpression> resources;

	public CPPTryStatement(CPPMethod method){
        super(method);
        catchs=new ArrayList<CPPCatchClauseStatement>();
        resources=new ArrayList<CPPVariableDeclarationExpression>();
	}

    public List<CPPCatchClauseStatement> getCatchs(){
        return catchs;
    }

    public void addCatch(CPPCatchClauseStatement s){
        catchs.add(s);
    }

    public CPPBlockStatement getFinallyBlock(){
        return finallyBlock;
    }

    public void setFinallyBlock(CPPBlockStatement s){
        this.finallyBlock=s;
    }

    public CPPBlockStatement getTryBlock(){
        return tryBlock;
    }

    public void setTryBlock(CPPBlockStatement s){
        this.tryBlock=s;
    }

    public List<CPPVariableDeclarationExpression> getResources(){
        return resources;
    }

    public void addResource(CPPVariableDeclarationExpression v){
        this.resources.add(v);
    }

}
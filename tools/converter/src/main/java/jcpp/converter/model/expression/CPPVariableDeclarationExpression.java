package jcpp.converter.model.expression;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.stmt.*;
import jcpp.converter.model.body.*;

public class CPPVariableDeclarationExpression extends CPPExpression{
    protected int modifiers;
    protected CPPType type;
    protected List<CPPVariableDeclarator> vars;

	public CPPVariableDeclarationExpression(CPPMethod method){
        super(method);
        vars=new ArrayList<CPPVariableDeclarator>();
	}

    public int getModifiers(){
        return modifiers;
    }

    public void setModifiers(int e){
        modifiers=e;
    }

    public CPPType getType(){
        return type;
    }

    public void setType(CPPType o){
        type=o;
    }

    public List<CPPVariableDeclarator> getVars(){
        return vars;
    }

    public void addVar(CPPVariableDeclarator e){
        vars.add(e);
    }
}
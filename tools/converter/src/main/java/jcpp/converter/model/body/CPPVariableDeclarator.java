package jcpp.converter.model.body;

import jcpp.converter.model.expression.*;

public class CPPVariableDeclarator{
	protected CPPVariableDeclaratorId id;
	protected CPPExpression init;

	public CPPVariableDeclarator(){
	}

	public CPPVariableDeclaratorId getId(){
		return id;
	}

	public void setId(CPPVariableDeclaratorId id){
		this.id=id;
	}

	public CPPExpression getInit(){
		return init;
	}

	public void setInit(CPPExpression i){
		init=i;
	}
}
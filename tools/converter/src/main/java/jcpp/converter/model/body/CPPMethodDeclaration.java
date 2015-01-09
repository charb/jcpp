package jcpp.converter.model.body;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.expression.*;
import jcpp.converter.model.stmt.*;

public class CPPMethodDeclaration extends CPPBodyDeclaration{
	protected int arrayCount;
	protected CPPBlockStatement body;
	protected int modifiers;
	protected String name;
	protected CPPNameExpression nameExpression;
	protected List<CPPParameter> parameters;
	protected CPPType type;

	public CPPMethodDeclaration(){
		parameters=new ArrayList<CPPParameter>();
	}

	public int getArrayCount(){
		return arrayCount;
	}

	public void setArrayCount(int m){
		arrayCount=m;
	}

	public CPPBlockStatement getBody(){
		return body;
	}

	public void setBody(CPPBlockStatement m){
		body=m;
	}

	public int getModifiers(){
		return modifiers;
	}

	public void setModifiers(int m){
		modifiers=m;
	}

	public String getName(){
		return name;
	}

	public void setName(String m){
		name=m;
	}

	public CPPNameExpression getNameExpression(){
		return nameExpression;
	}

	public void setNameExpression(CPPNameExpression m){
		nameExpression=m;
	}

	public List<CPPParameter> getParameters(){
		return parameters;
	}

	public void addParameter(CPPParameter b){
		parameters.add(b);
	}
	
	public CPPType getType(){
		return type;
	}

	public void setType(CPPType m){
		type=m;
	}
}
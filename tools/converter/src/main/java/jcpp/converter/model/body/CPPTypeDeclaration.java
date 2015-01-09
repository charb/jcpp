package jcpp.converter.model.body;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.expression.*;
import jcpp.converter.model.stmt.*;

public class CPPTypeDeclaration extends CPPBodyDeclaration{
	protected List<CPPBodyDeclaration> members;
	protected int modifiers;
	protected String name;
	protected CPPNameExpression nameExpression;

	public CPPTypeDeclaration(){
		members=new ArrayList<CPPBodyDeclaration>();
	}

	public List<CPPBodyDeclaration> getMembers(){
		return members;
	}

	public void addMember(CPPBodyDeclaration b){
		members.add(b);
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
}
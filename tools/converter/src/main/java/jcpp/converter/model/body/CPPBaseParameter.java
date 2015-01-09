package jcpp.converter.model.body;

public class CPPBaseParameter{
	protected int modifiers;
	protected CPPVariableDeclaratorId id;

	public CPPBaseParameter(){
	}

	public int getModifiers(){
		return modifiers;
	}

	public void setModifiers(int m){
		modifiers=m;
	}

	public CPPVariableDeclaratorId getId(){
		return id;
	}

	public void setId(CPPVariableDeclaratorId id){
		this.id=id;
	}
}
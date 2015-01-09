package jcpp.converter.model.body;

public class CPPVariableDeclaratorId{
	protected int arrayCount;
	protected String name;

	public CPPVariableDeclaratorId(){
	}

	public int getArrayCount(){
		return arrayCount;
	}

	public void setArrayCount(int i){
		arrayCount=i;
	}

	public String getName(){
		return name;
	}

	public void setName(String s){
		this.name=s;
	}
}
package jcpp.converter.model.body;

import jcpp.converter.model.*;

public class CPPParameter extends CPPBaseParameter{
	protected CPPType type;
	protected boolean bIsVarArgs;

	public CPPParameter(){
	}

	public boolean isVarArgs(){
		return bIsVarArgs;
	}

	public void setIsVarArgs(boolean m){
		bIsVarArgs=m;
	}

	public CPPType getType(){
		return type;
	}

	public void setType(CPPType id){
		this.type=id;
	}
}
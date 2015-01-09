package jcpp.converter.model.body;

import java.util.*;
import jcpp.converter.model.*;

public class CPPMultiTypeParameter extends CPPBaseParameter{
	protected List<CPPType> types;

	public CPPMultiTypeParameter(){
		types=new ArrayList<CPPType>();
	}

	public List<CPPType> getTypes(){
		return types;
	}

	public void addType(CPPType t){
		types.add(t);
	}
}
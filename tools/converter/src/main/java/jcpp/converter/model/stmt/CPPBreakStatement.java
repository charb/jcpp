package jcpp.converter.model.stmt;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.expression.*;

public class CPPBreakStatement extends CPPStatement{
    protected String id;

	public CPPBreakStatement(CPPMethod method){
        super(method);
	}

    public String getId(){
        return id;
    }

    public void setId(String s){
    	this.id=s;
    }
}
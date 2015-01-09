package jcpp.converter.model.stmt;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.expression.*;

public class CPPContinueStatement extends CPPStatement{
    protected String id;

	public CPPContinueStatement(CPPMethod method){
        super(method);
	}

    public String getId(){
        return id;
    }

    public void setId(String s){
    	this.id=s;
    }
}
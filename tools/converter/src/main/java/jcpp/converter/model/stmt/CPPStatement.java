package jcpp.converter.model.stmt;

import java.util.*;
import jcpp.converter.model.*;

public class CPPStatement{
    protected CPPMethod method;

	public CPPStatement(CPPMethod method){
        this.method=method;
	}

    public CPPMethod getMethod(){
        return method;
    }
}
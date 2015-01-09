package jcpp.converter.model.stmt;

import java.util.*;
import jcpp.converter.model.*;

public class CPPBlockStatement extends CPPStatement{
    protected List<CPPStatement> statements;

	public CPPBlockStatement(CPPMethod method){
        super(method);
        statements=new ArrayList<CPPStatement>();
	}

    public List<CPPStatement> getStatements(){
        return statements;
    }

    public void addStatement(CPPStatement statement){
    	statements.add(statement);
    }
}
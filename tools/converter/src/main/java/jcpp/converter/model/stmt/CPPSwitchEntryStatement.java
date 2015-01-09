package jcpp.converter.model.stmt;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.expression.*;

public class CPPSwitchEntryStatement extends CPPStatement{
    protected CPPExpression label;
    protected List<CPPStatement> statements;

	public CPPSwitchEntryStatement(CPPMethod method){
        super(method);
        statements=new ArrayList<CPPStatement>();
	}

    public CPPExpression getLabel(){
        return label;
    }

    public void setLabel(CPPExpression l){
        label=l;
    }

    public List<CPPStatement> getStatements(){
        return statements;
    }

    public void addStatement(CPPStatement statement){
    	statements.add(statement);
    }
}
package jcpp.converter.model.stmt;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.expression.*;

public class CPPSwitchStatement extends CPPStatement{
    protected CPPExpression selector;
    protected List<CPPSwitchEntryStatement> entries;

	public CPPSwitchStatement(CPPMethod method){
        super(method);
        entries=new ArrayList<CPPSwitchEntryStatement>();
	}

    public CPPExpression getSelector(){
        return selector;
    }

    public void setSelector(CPPExpression l){
        selector=l;
    }

    public List<CPPSwitchEntryStatement> getEntries(){
        return entries;
    }

    public void addEntry(CPPSwitchEntryStatement e){
    	entries.add(e);
    }
}
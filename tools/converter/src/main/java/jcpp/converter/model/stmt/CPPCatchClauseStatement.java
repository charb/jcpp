package jcpp.converter.model.stmt;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.body.*;

public class CPPCatchClauseStatement extends CPPStatement{
    protected CPPBlockStatement catchBlock;
    protected CPPMultiTypeParameter except;

	public CPPCatchClauseStatement(CPPMethod method){
        super(method);
	}

    public CPPBlockStatement getCatchBlock(){
        return catchBlock;
    }

    public void setCatchBlock(CPPBlockStatement s){
    	catchBlock=s;
    }

    public CPPMultiTypeParameter getExcept(){
        return except;
    }

    public void setExcept(CPPMultiTypeParameter e){
        except=e;
    }
}
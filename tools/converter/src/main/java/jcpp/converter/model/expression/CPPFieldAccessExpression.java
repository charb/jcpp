package jcpp.converter.model.expression;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.stmt.*;

public class CPPFieldAccessExpression extends CPPExpression{
    protected List<CPPType> typeArgs;
    protected String field;
    protected CPPNameExpression fieldExpression;
    protected CPPExpression scope;

	public CPPFieldAccessExpression(CPPMethod method){
        super(method);
        typeArgs=new ArrayList<CPPType>();
	}

    public List<CPPType> getTypeArgs(){
        return typeArgs;
    }

    public void addTypeArg(CPPType e){
        typeArgs.add(e);
    }

    public String getField(){
        return field;
    }

    public void setField(String f){
        field=f;
    }

    public CPPNameExpression getFieldExpression(){
        return fieldExpression;
    }

    public void setFieldExpression(CPPNameExpression e){
        fieldExpression=e;
    }

    public CPPExpression getScope(){
        return scope;
    }

    public void setScope(CPPExpression e){
        scope=e;
    }
}
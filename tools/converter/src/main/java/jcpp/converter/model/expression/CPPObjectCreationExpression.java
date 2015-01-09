package jcpp.converter.model.expression;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.stmt.*;
import jcpp.converter.model.body.*;

//when is it possible to have a non null scope
public class CPPObjectCreationExpression extends CPPExpression{
    protected List<CPPBodyDeclaration> anonymousClassBody;
    protected List<CPPExpression> args;
    protected CPPExpression scope;
    protected CPPType type;
    protected List<CPPType> typeArgs;

	public CPPObjectCreationExpression(CPPMethod method){
        super(method);
        anonymousClassBody=new ArrayList<CPPBodyDeclaration>();
        args=new ArrayList<CPPExpression>();
        typeArgs=new ArrayList<CPPType>();
	}

    public List<CPPBodyDeclaration> getAnonymousClassBody(){
        return anonymousClassBody;
    }

    public void addAnonymousClassBody(CPPBodyDeclaration e){
        anonymousClassBody.add(e);
    }

    public List<CPPExpression> getArgs(){
        return args;
    }

    public void addArg(CPPExpression e){
        args.add(e);
    }

    public void setScope(CPPExpression s){
        scope=s;
    }

    public CPPExpression getScope(){
        return scope;
    }

    public CPPType getType(){
        return type;
    }

    public void setType(CPPType t){
        type=t;
    }

    public List<CPPType> getTypeArgs(){
        return typeArgs;
    }

    public void addTypeArg(CPPType e){
        typeArgs.add(e);
    }
}
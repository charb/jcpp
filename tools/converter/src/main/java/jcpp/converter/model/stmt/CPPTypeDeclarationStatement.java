package jcpp.converter.model.stmt;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.expression.*;
import jcpp.converter.model.body.*;

public class CPPTypeDeclarationStatement extends CPPStatement{
    protected CPPTypeDeclaration typeDeclaration;

	public CPPTypeDeclarationStatement(CPPMethod method){
        super(method);
	}

    public CPPTypeDeclaration getTypeDeclaration(){
        return typeDeclaration;
    }

    public void setTypeDeclaration(CPPTypeDeclaration m){
        this.typeDeclaration=m;
    }
}
package jcpp.model.cpp.ast.expr.init;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.expr.*;
import org.eclipse.cdt.core.dom.ast.*;
import java.util.*;

public class ASTInitializerClauseFactory{

	public static void fillClasses(List<Class> c){
	}

	public static ASTInitializerClause create(IASTInitializerClause clause) throws Exception{
		return ASTExpressionFactory.create((IASTExpression)clause);
	}
}
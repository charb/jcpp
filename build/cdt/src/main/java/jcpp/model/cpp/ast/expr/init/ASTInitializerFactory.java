package jcpp.model.cpp.ast.expr.init;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.expr.init.c.*;
import jcpp.model.cpp.ast.expr.init.cpp.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.c.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import java.util.*;

public class ASTInitializerFactory{

	public static void fillClasses(List<Class> c){
		c.add(ASTCPPConstructorChainInitializer.class);
		c.add(ASTCPPConstructorInitializer.class);
		c.add(ASTCDesignatedInitializer.class);
		c.add(ASTEqualsInitializer.class);
		c.add(ASTInitializerList.class);
		c.add(ASTInitializer.class);
	}

	public static ASTInitializer create(IASTInitializer clause) throws Exception{
		if (clause instanceof ICPPASTConstructorChainInitializer){
			return new ASTCPPConstructorChainInitializer((ICPPASTConstructorChainInitializer)clause);

		}else if (clause instanceof ICPPASTConstructorInitializer){
			return new ASTCPPConstructorInitializer((ICPPASTConstructorInitializer)clause);

		}else if (clause instanceof ICASTDesignatedInitializer){
			return new ASTCDesignatedInitializer((ICASTDesignatedInitializer)clause);

		}else if (clause instanceof IASTEqualsInitializer){
			return new ASTEqualsInitializer((IASTEqualsInitializer)clause);

		}else if (clause instanceof IASTInitializerList){
			return new ASTInitializerList((IASTInitializerList)clause);

		}else{
			return new ASTInitializer(clause);
		}
	}
}
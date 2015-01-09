package jcpp.model.cpp.ast.ptr;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.ptr.c.*;
import jcpp.model.cpp.ast.ptr.cpp.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.c.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import java.util.*;

public class ASTPointerOperatorFactory extends ASTNode{

	public static void fillClasses(List<Class> c){
		c.add(ASTCPointer.class);
		c.add(ASTCPPPointerToMember.class);
		c.add(ASTCPPReferenceOperator.class);
		c.add(ASTPointer.class);
		c.add(ASTPointerOperator.class);
	}

	public static ASTPointerOperator create(IASTPointerOperator o) throws Exception{
		if (o instanceof ICASTPointer){
			return new ASTCPointer((ICASTPointer)o);

		}else if (o instanceof ICPPASTPointerToMember){
			return new ASTCPPPointerToMember((ICPPASTPointerToMember)o);

		}else if (o instanceof ICPPASTReferenceOperator){
			return new ASTCPPReferenceOperator((ICPPASTReferenceOperator)o);

		}else if (o instanceof IASTPointer){
			return new ASTPointer((IASTPointer)o);

		}else {
			return new ASTPointerOperator(o);
		}
	}
}
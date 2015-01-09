package jcpp.model.cpp.ast.declarator;

import jcpp.model.cpp.ast.declarator.cpp.*;
import jcpp.model.cpp.ast.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import java.util.*;

public class ASTDeclaratorFactory{

	public static void fillClasses(List<Class> c){
		c.add(ASTCPPArrayDeclarator.class);
		c.add(ASTCPPFieldDeclarator.class);
		c.add(ASTCPPFunctionDeclarator.class);
		c.add(ASTCPPDeclarator.class);
		c.add(ASTArrayDeclarator.class);
		c.add(ASTFieldDeclarator.class);
		c.add(ASTStandardFunctionDeclarator.class);
		c.add(ASTFunctionDeclarator.class);
		c.add(ASTDeclarator.class);
	}

	public static ASTDeclarator create(IASTDeclarator s) throws Exception {
		if (s instanceof ICPPASTArrayDeclarator){
			return new ASTCPPArrayDeclarator((ICPPASTArrayDeclarator)s);

		}else if (s instanceof ICPPASTFieldDeclarator){
			return new ASTCPPFieldDeclarator((ICPPASTFieldDeclarator)s);

		}else if (s instanceof ICPPASTFunctionDeclarator){
			return new ASTCPPFunctionDeclarator((ICPPASTFunctionDeclarator)s);

		}else if (s instanceof IASTArrayDeclarator){
			return new ASTArrayDeclarator((IASTArrayDeclarator)s);
		
		}else if (s instanceof IASTFieldDeclarator){
			return new ASTFieldDeclarator((IASTFieldDeclarator)s);

		}else if (s instanceof IASTStandardFunctionDeclarator){
			return new ASTStandardFunctionDeclarator((IASTStandardFunctionDeclarator)s);
		
		}else if (s instanceof IASTFunctionDeclarator){
			return new ASTFunctionDeclarator((IASTFunctionDeclarator)s);
			
		}else if (s instanceof ICPPASTDeclarator){
			return new ASTCPPDeclarator((ICPPASTDeclarator)s);

		}else{
			return new ASTDeclarator(s);
		}
	}
}
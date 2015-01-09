package jcpp.model.cpp.ast.expr;

import jcpp.model.cpp.ast.expr.c.*;
import jcpp.model.cpp.ast.expr.cpp.*;
import jcpp.model.cpp.ast.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.c.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import java.util.*;

public class ASTExpressionFactory{

	public static void fillClasses(List<Class> c){
		c.add(ASTCPPUnaryExpression.class);
		c.add(ASTCPPTypeIdExpression.class);
		c.add(ASTCPPSimpleTypeConstructorExpression.class);
		c.add(ASTCPPPackExpansionExpression.class);
		c.add(ASTCPPNewExpression.class);
		c.add(ASTCPPLiteralExpression.class);
		c.add(ASTCPPFieldReference.class);
		c.add(ASTCPPBinaryExpression.class);
		c.add(ASTCPPArraySubscriptExpression.class);
		c.add(ASTCPPCastExpression.class);
		c.add(ASTCPPDeleteExpression.class);
		c.add(ASTCPPFunctionCallExpression.class);
		c.add(ASTCPPExpressionList.class);
		c.add(ASTCPPExpression.class);
		c.add(ASTCTypeIdInitializerExpression.class);
		c.add(ASTArraySubscriptExpression.class);
		c.add(ASTBinaryExpression.class);
		c.add(ASTBinaryTypeIdExpression.class);
		c.add(ASTCastExpression.class);
		c.add(ASTConditionalExpression.class);
		c.add(ASTUnaryExpression.class);
		c.add(ASTTypeIdInitializerExpression.class);
		c.add(ASTTypeIdExpression.class);
		c.add(ASTProblemExpression.class);
		c.add(ASTFieldReferenceExpression.class);
		c.add(ASTIdExpression.class);
		c.add(ASTFunctionCallExpression.class);
		c.add(ASTLiteralExpression.class);
		c.add(ASTExpressionList.class);
		c.add(ASTExpression.class);
	}

	public static ASTExpression create(IASTExpression expr) throws Exception{
		if (expr instanceof ICPPASTUnaryExpression){
			return new ASTCPPUnaryExpression((ICPPASTUnaryExpression)expr);

		}else if (expr instanceof ICPPASTTypeIdExpression){
			return new ASTCPPTypeIdExpression((ICPPASTTypeIdExpression)expr);
		
		}else if (expr instanceof ICPPASTSimpleTypeConstructorExpression){
			return new ASTCPPSimpleTypeConstructorExpression((ICPPASTSimpleTypeConstructorExpression)expr);

		}else if (expr instanceof ICPPASTPackExpansionExpression){
			return new ASTCPPPackExpansionExpression((ICPPASTPackExpansionExpression)expr);

		}else if (expr instanceof ICPPASTNewExpression){
			return new ASTCPPNewExpression((ICPPASTNewExpression)expr);
		
		}else if (expr instanceof ICPPASTLiteralExpression){
			return new ASTCPPLiteralExpression((ICPPASTLiteralExpression)expr);
		
		}else if (expr instanceof ICPPASTFieldReference){
			return new ASTCPPFieldReference((ICPPASTFieldReference)expr);

		}else if (expr instanceof ICPPASTBinaryExpression){
			return new ASTCPPBinaryExpression((ICPPASTBinaryExpression)expr);

		}else if (expr instanceof ICPPASTArraySubscriptExpression){
			return new ASTCPPArraySubscriptExpression((ICPPASTArraySubscriptExpression)expr);
		
		}else if (expr instanceof ICPPASTCastExpression){
			return new ASTCPPCastExpression((ICPPASTCastExpression)expr);
		
		}else if (expr instanceof ICPPASTDeleteExpression){
			return new ASTCPPDeleteExpression((ICPPASTDeleteExpression)expr);

		}else if (expr instanceof ICPPASTFunctionCallExpression){
			return new ASTCPPFunctionCallExpression((ICPPASTFunctionCallExpression)expr);
		
		}else if (expr instanceof ICPPASTExpressionList){
			return new ASTCPPExpressionList((ICPPASTExpressionList)expr);
			
		}else if (expr instanceof ICASTTypeIdInitializerExpression){
			return new ASTCTypeIdInitializerExpression((ICASTTypeIdInitializerExpression)expr);
		
		}else if (expr instanceof IASTArraySubscriptExpression){
			return new ASTArraySubscriptExpression((IASTArraySubscriptExpression)expr);
			
		}else if (expr instanceof IASTBinaryExpression){
			return new ASTBinaryExpression((IASTBinaryExpression)expr);
		
		}else if (expr instanceof IASTBinaryTypeIdExpression){
			return new ASTBinaryTypeIdExpression((IASTBinaryTypeIdExpression)expr);
		
		}else if (expr instanceof IASTCastExpression){
			return new ASTCastExpression((IASTCastExpression)expr);
		
		}else if (expr instanceof IASTConditionalExpression){
			return new ASTConditionalExpression((IASTConditionalExpression)expr);
		
		}else if (expr instanceof IASTUnaryExpression){
			return new ASTUnaryExpression((IASTUnaryExpression)expr);
			 
		}else if (expr instanceof IASTTypeIdInitializerExpression){
			return new ASTTypeIdInitializerExpression((IASTTypeIdInitializerExpression)expr);
			 
		}else if (expr instanceof IASTTypeIdExpression){
			return new ASTTypeIdExpression((IASTTypeIdExpression)expr);
		
		}else if (expr instanceof IASTProblemExpression){
			 return new ASTProblemExpression((IASTProblemExpression)expr);
		
		}else if (expr instanceof IASTFieldReference){
			return new ASTFieldReferenceExpression((IASTFieldReference)expr);
			 
		}else if (expr instanceof IASTIdExpression){
			return new ASTIdExpression((IASTIdExpression)expr);

		}else if (expr instanceof IASTFunctionCallExpression){
			return new ASTFunctionCallExpression((IASTFunctionCallExpression)expr);
			
		}else if (expr instanceof IASTLiteralExpression){
			return new ASTLiteralExpression((IASTLiteralExpression)expr);

		}else if (expr instanceof IASTExpressionList){
			return new ASTExpressionList((IASTExpressionList)expr);
		
		}else{
			throw new Exception("unknown expression type "+expr.getClass());
		}

		/* if (expr instanceof ICPPASTExpression){
			return new ASTCPPExpression((ICPPASTExpression)expr);
			
		}else{
			return new ASTExpression(expr);
		}*/
	}
}
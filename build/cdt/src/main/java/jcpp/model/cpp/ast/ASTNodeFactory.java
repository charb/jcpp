package jcpp.model.cpp.ast;

import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.c.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import jcpp.model.cpp.ast.location.*;
import jcpp.model.cpp.ast.stmt.*;
import jcpp.model.cpp.ast.ptr.*;
import jcpp.model.cpp.ast.cpp.*;
import jcpp.model.cpp.ast.c.*;
import jcpp.model.cpp.ast.name.*;
import jcpp.model.cpp.ast.macro.*;
import jcpp.model.cpp.ast.id.*;
import jcpp.model.cpp.ast.expr.*;
import jcpp.model.cpp.ast.expr.init.*;
import jcpp.model.cpp.ast.declarator.*;
import jcpp.model.cpp.ast.declaration.*;
import jcpp.model.cpp.ast.declaration.specifier.*;
import jcpp.model.cpp.ast.attribute.*;
import java.util.*;

public class ASTNodeFactory{

	public static List<Class> getClasses() throws Exception{
		List<Class> c=new ArrayList<Class>();

		c.add(ASTComment.class);
		c.add(ASTProblem.class);
		c.add(ASTTranslationUnit.class);
		ASTStatementFactory.fillClasses(c);
		ASTPointerOperatorFactory.fillClasses(c);
		ASTNameFactory.fillClasses(c);
		ASTPreprocessorStatementFactory.fillClasses(c);
		ASTTypeIdFactory.fillClasses(c);
		ASTNodeLocationFactory.fillClasses(c);
		ASTExpressionFactory.fillClasses(c);
		ASTInitializerFactory.fillClasses(c);
		ASTInitializerClauseFactory.fillClasses(c);
		ASTDeclaratorFactory.fillClasses(c);
		ASTArrayModifierFactory.fillClasses(c);
		ASTCPPTemplateParameterFactory.fillClasses(c);
		ASTCDesignatorFactory.fillClasses(c);
		ASTAttributeFactory.fillClasses(c);
		ASTAttributeSpecifierFactory.fillClasses(c);
		ASTDeclSpecifierFactory.fillClasses(c); 
		ASTDeclarationFactory.fillClasses(c);
		return c;
	}
	
	public static ASTNode create(IASTNode node) throws Exception{
		if (node instanceof IASTComment){
			return new ASTComment((IASTComment)node);

		}else if (node instanceof IASTProblem){
			return new ASTProblem((IASTProblem)node);

		}else if (node instanceof IASTTranslationUnit){
			return new ASTTranslationUnit((IASTTranslationUnit)node);

		}else if (node instanceof IASTStatement){
			return ASTStatementFactory.create((IASTStatement)node);

		}else if (node instanceof IASTPointerOperator){
			return ASTPointerOperatorFactory.create((IASTPointerOperator)node);
		
		}else if (node instanceof IASTName){
			return ASTNameFactory.create((IASTName)node);

		}else if (node instanceof IASTPreprocessorStatement){
			return ASTPreprocessorStatementFactory.create((IASTPreprocessorStatement)node);

		}else if (node instanceof IASTTypeId){
			return ASTTypeIdFactory.create((IASTTypeId)node);
		
		}else if (node instanceof IASTExpression){
			return ASTExpressionFactory.create((IASTExpression)node);
		
		}else if (node instanceof IASTInitializer){
			return ASTInitializerFactory.create((IASTInitializer)node);
		
		}else if (node instanceof IASTInitializerClause){
			 return ASTInitializerClauseFactory.create((IASTInitializerClause)node);
		
		}else if (node instanceof IASTDeclarator){
			return ASTDeclaratorFactory.create((IASTDeclarator)node);
		
		}else if (node instanceof IASTArrayModifier){
			return ASTArrayModifierFactory.create((IASTArrayModifier)node);
		
		}else if (node instanceof ICPPASTTemplateParameter){
			return ASTCPPTemplateParameterFactory.create((ICPPASTTemplateParameter)node);

		}else if (node instanceof ICASTDesignator){
			return ASTCDesignatorFactory.create((ICASTDesignator)node);
		
		}else if (node instanceof IASTAttribute){
			return ASTAttributeFactory.create((IASTAttribute)node);
		
		}else if (node instanceof IASTAttributeSpecifier){
			return ASTAttributeSpecifierFactory.create((IASTAttributeSpecifier)node);
		
		}else if (ASTDeclSpecifierFactory.handleNode(node)){
			return ASTDeclSpecifierFactory.create(node); 

		}else{
			return ASTDeclarationFactory.create(node);
		}
	}
}
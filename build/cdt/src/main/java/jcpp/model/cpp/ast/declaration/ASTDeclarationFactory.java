package jcpp.model.cpp.ast.declaration;

import jcpp.model.cpp.ast.declaration.cpp.*;
import jcpp.model.cpp.ast.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import java.util.*;

public class ASTDeclarationFactory{

	public static void fillClasses(List<Class> c) throws Exception {
		c.add(ASTCPPVisibilityLabel.class);
		c.add(ASTCPPUsingDirective.class);
		c.add(ASTCPPUsingDeclaration.class);
		c.add(ASTCPPAliasDeclaration.class);
		c.add(ASTCPPExplicitTemplateInstantiation.class);
		c.add(ASTCPPFunctionDefinition.class);
		c.add(ASTCPPFunctionWithTryBlock.class);
		c.add(ASTCPPLinkageSpecification.class);
		c.add(ASTCPPNamespaceAlias.class);
		c.add(ASTCPPNamespaceDefinition.class);
		c.add(ASTCPPStaticAssertDeclaration.class);
		c.add(ASTCPPTemplateDeclaration.class);
		c.add(ASTCPPTemplateSpecialization.class);
		c.add(ASTASMDeclaration.class);
		c.add(ASTProblemDeclaration.class);
		c.add(ASTFunctionDefinition.class);
		c.add(ASTSimpleDeclaration.class);
		c.add(ASTCPPParameterDeclaration.class);
	}

	public static ASTNode create(IASTNode s) throws Exception {
		if (s instanceof ICPPASTVisibilityLabel){
			return new ASTCPPVisibilityLabel((ICPPASTVisibilityLabel)s);

		}else if (s instanceof ICPPASTUsingDirective){
			return new ASTCPPUsingDirective((ICPPASTUsingDirective)s);

		}else if (s instanceof ICPPASTUsingDeclaration){
			return new ASTCPPUsingDeclaration((ICPPASTUsingDeclaration)s);

		}else if (s instanceof ICPPASTAliasDeclaration){
			return new ASTCPPAliasDeclaration((ICPPASTAliasDeclaration)s);

		}else if (s instanceof ICPPASTExplicitTemplateInstantiation){
			return new ASTCPPExplicitTemplateInstantiation((ICPPASTExplicitTemplateInstantiation)s);

		}else if (s instanceof ICPPASTFunctionDefinition){
			return new ASTCPPFunctionDefinition((ICPPASTFunctionDefinition)s);

		}else if (s instanceof ICPPASTFunctionWithTryBlock){
			return new ASTCPPFunctionWithTryBlock((ICPPASTFunctionWithTryBlock)s);

		}else if (s instanceof ICPPASTLinkageSpecification){
			return new ASTCPPLinkageSpecification((ICPPASTLinkageSpecification)s);

		}else if (s instanceof ICPPASTNamespaceAlias){
			return new ASTCPPNamespaceAlias((ICPPASTNamespaceAlias)s);

		}else if (s instanceof ICPPASTNamespaceDefinition){
			return new ASTCPPNamespaceDefinition((ICPPASTNamespaceDefinition)s);

		}else if (s instanceof ICPPASTStaticAssertDeclaration){
			return new ASTCPPStaticAssertDeclaration((ICPPASTStaticAssertDeclaration)s);

		}else if (s instanceof ICPPASTTemplateDeclaration){
			return new ASTCPPTemplateDeclaration((ICPPASTTemplateDeclaration)s);
		
		}else if (s instanceof ICPPASTTemplateSpecialization){
			return new ASTCPPTemplateSpecialization((ICPPASTTemplateSpecialization)s);

		}else if (s instanceof IASTASMDeclaration){
			return new ASTASMDeclaration((IASTASMDeclaration)s);

		}else if (s instanceof IASTProblemDeclaration){
			return new ASTProblemDeclaration((IASTProblemDeclaration)s);
		
		}else if (s instanceof IASTFunctionDefinition){
			return new ASTFunctionDefinition((IASTFunctionDefinition)s);

		}else if (s instanceof IASTSimpleDeclaration){
			return new ASTSimpleDeclaration((IASTSimpleDeclaration)s);
		
		}else if (s instanceof ICPPASTParameterDeclaration){
			return new ASTCPPParameterDeclaration((ICPPASTParameterDeclaration)s);
		}

		throw new Exception("unknown declaration "+s);
	}
}
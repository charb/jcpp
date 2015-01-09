package jcpp.model.cpp.ast.declaration;

import jcpp.model.cpp.ast.declaration.specifier.*;
import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.declarator.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTParameterDeclaration extends ASTNode{
	@XmlElement
	private ASTNodeWrapper<ASTDeclarator> declarator;
	@XmlElement
	private ASTNodeWrapper<ASTDeclSpecifier> declSpecifier;

	public ASTParameterDeclaration(IASTParameterDeclaration d) throws Exception{
		declarator=new ASTNodeWrapper<ASTDeclarator>();
		if (d.getDeclarator()!=null){
			declarator.set(ASTDeclaratorFactory.create(d.getDeclarator()));
		}

		declSpecifier=new ASTNodeWrapper<ASTDeclSpecifier>();
		if (d.getDeclSpecifier()!=null){
			declSpecifier.set((ASTDeclSpecifier)ASTDeclSpecifierFactory.create(d.getDeclSpecifier()));
		}
	}

	public ASTParameterDeclaration(){
		declarator=new ASTNodeWrapper<ASTDeclarator>();
		declSpecifier=new ASTNodeWrapper<ASTDeclSpecifier>();
	}

	public ASTDeclarator getDeclarator(){
		return declarator.get();
	}

	public void setDeclarator(ASTDeclarator d){
		declarator.set(d);
	}

	public ASTDeclSpecifier getDeclSpecifier(){
		return declSpecifier.get();
	}

	public void setDeclSpecifier(ASTDeclSpecifier s){
		declSpecifier.set(s);
	}
}
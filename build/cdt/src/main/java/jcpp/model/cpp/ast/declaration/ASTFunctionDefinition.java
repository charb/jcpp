package jcpp.model.cpp.ast.declaration;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.stmt.*;
import jcpp.model.cpp.ast.declarator.*;
import jcpp.model.cpp.ast.declaration.specifier.*;
import org.eclipse.cdt.core.dom.ast.*;
import java.util.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTFunctionDefinition extends ASTDeclaration{
	@XmlElement
	private ASTNodeWrapper<ASTStatement> body;
	@XmlElement
	private ASTNodeWrapper<ASTFunctionDeclarator> declarator;
	@XmlElement
	private ASTNodeWrapper<ASTDeclSpecifier> declSpecifier;

	public ASTFunctionDefinition(IASTFunctionDefinition d) throws Exception{
		super(d);
		body=new ASTNodeWrapper<ASTStatement>();
		if (d.getBody()!=null){
			body.set(ASTStatementFactory.create(d.getBody()));
		}

		declarator=new ASTNodeWrapper<ASTFunctionDeclarator>();
		if (d.getDeclarator()!=null){
			declarator.set((ASTFunctionDeclarator)ASTDeclaratorFactory.create(d.getDeclarator()));
		}

		declSpecifier=new ASTNodeWrapper<ASTDeclSpecifier>();
		if (d.getDeclSpecifier()!=null){
			declSpecifier.set((ASTDeclSpecifier)ASTDeclSpecifierFactory.create(d.getDeclSpecifier()));
		}
	}

	public ASTFunctionDefinition(){
		body=new ASTNodeWrapper<ASTStatement>();
		declarator=new ASTNodeWrapper<ASTFunctionDeclarator>();
		declSpecifier=new ASTNodeWrapper<ASTDeclSpecifier>();
	}

	public ASTStatement getBody(){
		return body.get();
	}

	public void setBody(ASTStatement d){
		body.set(d);
	}

	public ASTFunctionDeclarator getDeclarator(){
		return declarator.get();
	}

	public void setDeclarator(ASTFunctionDeclarator d){
		declarator.set(d);
	}

	public ASTDeclSpecifier getDeclSpecifier(){
		return declSpecifier.get();
	}

	public void setDeclSpecifier(ASTDeclSpecifier d){
		declSpecifier.set(d);
	}
}
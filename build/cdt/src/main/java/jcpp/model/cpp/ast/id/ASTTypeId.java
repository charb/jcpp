package jcpp.model.cpp.ast.id;

import org.eclipse.cdt.core.dom.ast.*;
import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.declarator.*;
import jcpp.model.cpp.ast.declaration.specifier.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTTypeId extends ASTNode{
	@XmlElement
	private ASTNodeWrapper<ASTDeclarator> declarator;
	@XmlElement
	private ASTNodeWrapper<ASTDeclSpecifier> declSpecifier;

	public ASTTypeId(IASTTypeId typeId) throws Exception{
		super(typeId);
		declarator=new ASTNodeWrapper<ASTDeclarator>();
		if (typeId.getAbstractDeclarator()!=null){
			declarator.set(ASTDeclaratorFactory.create(typeId.getAbstractDeclarator()));
		}

		declSpecifier=new ASTNodeWrapper<ASTDeclSpecifier>();
		if (typeId.getDeclSpecifier()!=null){
			declSpecifier.set((ASTDeclSpecifier)ASTDeclSpecifierFactory.create(typeId.getDeclSpecifier()));
		}
	}

	public ASTTypeId(){
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

	public void setDeclSpecifier(ASTDeclSpecifier d){
		declSpecifier.set(d);
	}
}
package jcpp.model.cpp.ast.declaration.cpp;

import jcpp.model.cpp.ast.declaration.*;
import jcpp.model.cpp.ast.name.*;
import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.declarator.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import java.util.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPLinkageSpecification extends ASTDeclaration{
	@XmlElement
	private String literal;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTDeclaration> declarations;

	public ASTCPPLinkageSpecification(ICPPASTLinkageSpecification d) throws Exception{
		super(d);

		declarations=new ArrayList<ASTDeclaration>();
		if (d.getDeclarations()!=null){
			for (IASTDeclaration de : d.getDeclarations()){
				declarations.add((ASTDeclaration)ASTDeclarationFactory.create(de));
			}
		}

		literal=d.getLiteral();
	}

	public ASTCPPLinkageSpecification(){
	}

	public List<ASTDeclaration> getDeclarations(){
		return declarations;
	}

	public void addDeclaration(ASTDeclaration d){
		declarations.add(d);
	}

	public String getLiteral(){
		return literal;
	}

	public void setLiteral(String n){
		literal=n;
	}
}
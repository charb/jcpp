package jcpp.model.cpp.ast.declaration;

import jcpp.model.cpp.ast.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
//TODO check ASTDeclarationListOwner
public class ASTDeclaration extends ASTNode{

	public ASTDeclaration(IASTDeclaration d) throws Exception{
		super(d);
	}

	public ASTDeclaration(){
	}
}
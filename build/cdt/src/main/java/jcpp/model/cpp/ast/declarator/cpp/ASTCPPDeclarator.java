package jcpp.model.cpp.ast.declarator.cpp;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.declarator.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPDeclarator extends ASTDeclarator{
	@XmlElement
	private boolean bDeclaresParameterPack;

	public ASTCPPDeclarator(ICPPASTDeclarator decl) throws Exception{
		super(decl);
		bDeclaresParameterPack=decl.declaresParameterPack();
	}

	public ASTCPPDeclarator(){
	}

	public boolean declaresParameterPack(){
		return bDeclaresParameterPack;
	}

	public void setDeclaresParameterPack(boolean b){
		bDeclaresParameterPack=b;
	}
}
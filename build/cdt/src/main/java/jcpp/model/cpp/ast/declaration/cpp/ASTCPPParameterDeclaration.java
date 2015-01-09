package jcpp.model.cpp.ast.declaration.cpp;

import jcpp.model.cpp.ast.declaration.*;
import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.declarator.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPParameterDeclaration extends ASTParameterDeclaration{
	@XmlElement
	private boolean bIsParameterPack;

	public ASTCPPParameterDeclaration(ICPPASTParameterDeclaration d) throws Exception{
		super(d);
		bIsParameterPack=d.isParameterPack();
	}

	public ASTCPPParameterDeclaration(){
	}

	public boolean isParameterPack(){
		return bIsParameterPack;
	}

	public void setParameterPack(boolean b){
		bIsParameterPack=b;
	}
}
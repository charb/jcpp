package jcpp.model.cpp.ast.declarator.cpp;

import jcpp.model.cpp.ast.declarator.*;
import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.name.*;
import jcpp.model.cpp.ast.ptr.*;
import jcpp.model.cpp.ast.expr.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPFieldDeclarator extends ASTFieldDeclarator{
	@XmlElement
	private boolean bDeclaresParameterPack;

	public ASTCPPFieldDeclarator(ICPPASTFieldDeclarator decl) throws Exception{
		super(decl);
		bDeclaresParameterPack=decl.declaresParameterPack();
	}

	public ASTCPPFieldDeclarator(){
	}

	public boolean declaresParameterPack(){
		return bDeclaresParameterPack;
	}

	public void setDeclaresParameterPack(boolean b){
		bDeclaresParameterPack=b;
	}
}
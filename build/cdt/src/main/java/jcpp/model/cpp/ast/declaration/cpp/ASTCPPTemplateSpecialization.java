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
public class ASTCPPTemplateSpecialization extends ASTDeclaration{
	@XmlElement
	private ASTNodeWrapper<ASTDeclaration> declaration;

	public ASTCPPTemplateSpecialization(ICPPASTTemplateSpecialization d) throws Exception{
		super(d);
		declaration=new ASTNodeWrapper<ASTDeclaration>();
		if (d.getDeclaration()!=null){
			declaration.set((ASTDeclaration)ASTDeclarationFactory.create(d.getDeclaration()));
		}
	}

	public ASTCPPTemplateSpecialization(){
		declaration=new ASTNodeWrapper<ASTDeclaration>();
	}

	public ASTDeclaration getDeclaration(){
		return declaration.get();
	}

	public void setDeclaration(ASTDeclaration d){
		declaration.set(d);
	}
}
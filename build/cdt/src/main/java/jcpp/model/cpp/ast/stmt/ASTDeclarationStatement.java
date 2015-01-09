package jcpp.model.cpp.ast.stmt;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.declaration.*;
import jcpp.model.cpp.ast.expr.*;
import jcpp.model.cpp.ast.expr.init.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTDeclarationStatement extends ASTStatement{
	@XmlElement
	private ASTNodeWrapper<ASTDeclaration> declaration;

	public ASTDeclarationStatement(IASTDeclarationStatement s) throws Exception{
		super(s);
		declaration=new ASTNodeWrapper<ASTDeclaration>();
		if (s.getDeclaration()!=null){
			declaration.set((ASTDeclaration)ASTDeclarationFactory.create(s.getDeclaration()));
		}
	}

	public ASTDeclarationStatement(){
		declaration=new ASTNodeWrapper<ASTDeclaration>();
	}

	public ASTDeclaration getDeclaration(){
		return declaration.get();
	}

	public void setDeclaration(ASTDeclaration s){
		declaration.set(s);
	}
}
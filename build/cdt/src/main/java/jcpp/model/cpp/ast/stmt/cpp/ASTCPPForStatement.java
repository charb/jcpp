package jcpp.model.cpp.ast.stmt.cpp;

import jcpp.model.cpp.ast.stmt.*;
import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.declaration.*;
import jcpp.model.cpp.ast.expr.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPForStatement extends ASTForStatement{
	@XmlElement
	private ASTNodeWrapper<ASTDeclaration> conditionDeclaration;

	public ASTCPPForStatement(ICPPASTForStatement s) throws Exception{
		super(s);
		conditionDeclaration=new ASTNodeWrapper<ASTDeclaration>();
		if (s.getConditionDeclaration()!=null){
			conditionDeclaration.set((ASTDeclaration)ASTDeclarationFactory.create(s.getConditionDeclaration()));
		}
	}

	public ASTCPPForStatement(){
		conditionDeclaration=new ASTNodeWrapper<ASTDeclaration>();
	}

	public ASTDeclaration getConditionDeclaration(){
		return conditionDeclaration.get();
	}

	public void setConditionDeclaration(ASTDeclaration s){
		conditionDeclaration.set(s);
	}
}
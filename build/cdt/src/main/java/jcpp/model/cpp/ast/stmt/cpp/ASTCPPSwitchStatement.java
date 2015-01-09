package jcpp.model.cpp.ast.stmt.cpp;

import jcpp.model.cpp.ast.stmt.*;
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
public class ASTCPPSwitchStatement extends ASTSwitchStatement{
	@XmlElement
	private ASTNodeWrapper<ASTDeclaration> controllerDeclaration;

	public ASTCPPSwitchStatement(ICPPASTSwitchStatement s) throws Exception{
		super(s);
		controllerDeclaration=new ASTNodeWrapper<ASTDeclaration>();
		if (s.getControllerDeclaration()!=null){
			controllerDeclaration.set((ASTDeclaration)ASTDeclarationFactory.create(s.getControllerDeclaration()));
		}
	}

	public ASTCPPSwitchStatement(){
		controllerDeclaration=new ASTNodeWrapper<ASTDeclaration>();
	}

	public ASTDeclaration getControllerDeclaration(){
		return controllerDeclaration.get();
	}

	public void setControllerDeclaration(ASTDeclaration s){
		controllerDeclaration.set(s);
	}
}
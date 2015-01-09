package jcpp.model.cpp.ast.stmt;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.expr.*;
import jcpp.model.cpp.ast.expr.init.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTSwitchStatement extends ASTStatement{
	@XmlElement
	private ASTNodeWrapper<ASTExpression> controllerExpression;
	@XmlElement
	private ASTNodeWrapper<ASTStatement> body;

	public ASTSwitchStatement(IASTSwitchStatement s) throws Exception{
		super(s);
		controllerExpression=new ASTNodeWrapper<ASTExpression>();
		if (s.getControllerExpression()!=null){
			controllerExpression.set(ASTExpressionFactory.create(s.getControllerExpression()));
		}

		body=new ASTNodeWrapper<ASTStatement>();
		if (s.getBody()!=null){
			body.set(ASTStatementFactory.create(s.getBody()));
		}
	}

	public ASTSwitchStatement(){
		controllerExpression=new ASTNodeWrapper<ASTExpression>();
		body=new ASTNodeWrapper<ASTStatement>();
	}

	public ASTExpression getControllerExpression(){
		return controllerExpression.get();
	}

	public void setControllerExpression(ASTExpression s){
		controllerExpression.set(s);
	}

	public ASTStatement getBody(){
		return body.get();
	}

	public void setBody(ASTStatement s){
		body.set(s);
	}
}
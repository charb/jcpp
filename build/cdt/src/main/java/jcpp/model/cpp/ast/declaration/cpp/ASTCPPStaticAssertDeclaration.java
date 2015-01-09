package jcpp.model.cpp.ast.declaration.cpp;

import jcpp.model.cpp.ast.declaration.*;
import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.expr.*;
import jcpp.model.cpp.ast.expr.cpp.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPStaticAssertDeclaration extends ASTDeclaration{
	@XmlElement
	private ASTNodeWrapper<ASTExpression> condition;
	@XmlElement
	private ASTNodeWrapper<ASTCPPLiteralExpression> message;

	public ASTCPPStaticAssertDeclaration(ICPPASTStaticAssertDeclaration d) throws Exception{
		super(d);
		condition=new ASTNodeWrapper<ASTExpression>();
		if (d.getCondition()!=null){
			condition.set(ASTExpressionFactory.create(d.getCondition()));
		}
		message=new ASTNodeWrapper<ASTCPPLiteralExpression>();
		if (d.getMessage()!=null){
			message.set((ASTCPPLiteralExpression)ASTExpressionFactory.create(d.getMessage()));
		}
	}

	public ASTCPPStaticAssertDeclaration(){
		condition=new ASTNodeWrapper<ASTExpression>();
		message=new ASTNodeWrapper<ASTCPPLiteralExpression>();
	}

	public ASTExpression getCondition(){
		return condition.get();
	}

	public void setCondition(ASTExpression e){
		condition.set(e);
	}

	public ASTCPPLiteralExpression getMessage(){
		return message.get();
	}

	public void setMessage(ASTCPPLiteralExpression e){
		message.set(e);
	}
}
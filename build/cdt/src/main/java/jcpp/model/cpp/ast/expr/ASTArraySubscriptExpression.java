package jcpp.model.cpp.ast.expr;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.expr.init.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTArraySubscriptExpression extends ASTExpression{
	@XmlElement
	private ASTNodeWrapper<ASTInitializerClause> argument;
	@XmlElement
	private ASTNodeWrapper<ASTExpression> arrayExpression;

	public ASTArraySubscriptExpression(IASTArraySubscriptExpression expr) throws Exception{
		super(expr);
		argument=new ASTNodeWrapper<ASTInitializerClause>();
		if (expr.getArgument()!=null){
			argument.set(ASTInitializerClauseFactory.create(expr.getArgument()));
		}

		arrayExpression=new ASTNodeWrapper<ASTExpression>();
		if (expr.getArrayExpression()!=null){
			arrayExpression.set(ASTExpressionFactory.create(expr.getArrayExpression()));
		}
	}

	public ASTArraySubscriptExpression(){
		argument=new ASTNodeWrapper<ASTInitializerClause>();
		arrayExpression=new ASTNodeWrapper<ASTExpression>();
	}

	public ASTInitializerClause getArgument(){
		return argument.get();
	}

	public void setArgument(ASTInitializerClause b){
		argument.set(b);
	}

	public ASTExpression getArrayExpression(){
		return arrayExpression.get();
	}

	public void setArrayExpression(ASTExpression b){
		arrayExpression.set(b);
	}
}
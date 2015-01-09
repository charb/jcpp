package jcpp.model.cpp.ast.expr;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.expr.init.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTConditionalExpression extends ASTExpression{
	@XmlElement
	private ASTNodeWrapper<ASTExpression> logicalConditionExpression;
	@XmlElement
	private ASTNodeWrapper<ASTExpression> negativeResultExpression;
	@XmlElement
	private ASTNodeWrapper<ASTExpression> positiveResultExpression;

	public ASTConditionalExpression(IASTConditionalExpression expr) throws Exception{
		super(expr);

		logicalConditionExpression=new ASTNodeWrapper<ASTExpression>();
		if (expr.getLogicalConditionExpression()!=null){
			logicalConditionExpression.set(ASTExpressionFactory.create(expr.getLogicalConditionExpression()));
		}

		negativeResultExpression=new ASTNodeWrapper<ASTExpression>();
		if (expr.getNegativeResultExpression()!=null){
			negativeResultExpression.set(ASTExpressionFactory.create(expr.getNegativeResultExpression()));
		}

		positiveResultExpression=new ASTNodeWrapper<ASTExpression>();
		if (expr.getPositiveResultExpression()!=null){
			positiveResultExpression.set(ASTExpressionFactory.create(expr.getPositiveResultExpression()));
		}
	}

	public ASTConditionalExpression(){
		logicalConditionExpression=new ASTNodeWrapper<ASTExpression>();
		negativeResultExpression=new ASTNodeWrapper<ASTExpression>();
		positiveResultExpression=new ASTNodeWrapper<ASTExpression>();
	}

	public ASTExpression getLogicalConditionExpression(){
		return logicalConditionExpression.get();
	}

	public void setLogicalConditionExpression(ASTExpression b){
		logicalConditionExpression.set(b);
	}

	public ASTExpression getNegativeResultExpression(){
		return negativeResultExpression.get();
	}

	public void setNegativeResultExpression(ASTExpression b){
		negativeResultExpression.set(b);
	}

	public ASTExpression getPositiveResultExpression(){
		return positiveResultExpression.get();
	}

	public void setPositiveResultExpression(ASTExpression b){
		positiveResultExpression.set(b);
	}
}
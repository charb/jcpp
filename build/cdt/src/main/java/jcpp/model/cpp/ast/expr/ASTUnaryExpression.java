package jcpp.model.cpp.ast.expr;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.expr.init.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTUnaryExpression extends ASTExpression{
	@XmlElement
	private ASTNodeWrapper<ASTExpression> operand;
	@XmlElement
	private String operator;

	public ASTUnaryExpression(IASTUnaryExpression expr) throws Exception{
		super(expr);
		operand=new ASTNodeWrapper<ASTExpression>();
		if (expr.getOperand()!=null){
			operand.set(ASTExpressionFactory.create(expr.getOperand()));
		}
		operator=getOperator(expr.getOperator());
	}

	public ASTUnaryExpression(){
		operand=new ASTNodeWrapper<ASTExpression>();
	}

	public ASTExpression getOperand(){
		return operand.get();
	}

	public void setOperand(ASTExpression b){
		operand.set(b);
	}

	public static String getOperator(int i){
		if (i==IASTUnaryExpression.op_alignOf){
			return "op_alignOf";
		}else if (i==IASTUnaryExpression.op_amper){
			return "op_amper";
		}else if (i==IASTUnaryExpression.op_bracketedPrimary){
			return "op_bracketedPrimary";
		}else if (i==IASTUnaryExpression.op_minus){
			return "op_minus";
		}else if (i==IASTUnaryExpression.op_noexcept){
			return "op_noexcept";
		}else if (i==IASTUnaryExpression.op_plus){
			return "op_plus";
		}else if (i==IASTUnaryExpression.op_postFixDecr){
			return "op_postFixDecr";
		}else if (i==IASTUnaryExpression.op_postFixIncr){
			return "op_postFixIncr";
		}else if (i==IASTUnaryExpression.op_prefixDecr){
			return "op_prefixDecr";
		}else if (i==IASTUnaryExpression.op_prefixIncr){
			return "op_prefixIncr";
		}else if (i==IASTUnaryExpression.op_sizeof){
			return "op_sizeof";
		}else if (i==IASTUnaryExpression.op_sizeofParameterPack){
			return "op_sizeofParameterPack";
		}else if (i==IASTUnaryExpression.op_star){
			return "op_star";
		}else if (i==IASTUnaryExpression.op_throw){
			return "op_throw";
		}else if (i==IASTUnaryExpression.op_tilde){
			return "op_tilde";
		}else if (i==IASTUnaryExpression.op_typeid){
			return "op_typeid";
		}else if (i==IASTUnaryExpression.op_typeof){
			return "op_typeof";
		}else{
			return "unkown";
		}
	}

	public String getOperator(){
		return operator;
	}

	public void setOperator(String b){
		operator=b;
	}
}
package jcpp.model.cpp.ast.expr;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.expr.init.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTBinaryExpression extends ASTExpression{
	@XmlElement
	private ASTNodeWrapper<ASTInitializerClause> initOperand2;
	@XmlElement
	private ASTNodeWrapper<ASTExpression> operand1;
	@XmlElement
	private ASTNodeWrapper<ASTExpression> operand2;
	@XmlElement
	private String operator;

	public ASTBinaryExpression(IASTBinaryExpression expr) throws Exception{
		super(expr);
		initOperand2=new ASTNodeWrapper<ASTInitializerClause>();
		if (expr.getInitOperand2()!=null){
			initOperand2.set(ASTInitializerClauseFactory.create(expr.getInitOperand2()));
		}

		operand1=new ASTNodeWrapper<ASTExpression>();
		if (expr.getOperand1()!=null){
			operand1.set(ASTExpressionFactory.create(expr.getOperand1()));
		}

		operand2=new ASTNodeWrapper<ASTExpression>();
		if (expr.getOperand2()!=null){
			operand2.set(ASTExpressionFactory.create(expr.getOperand2()));
		}
		operator=getOperator(expr.getOperator());
	}

	public ASTBinaryExpression(){
		initOperand2=new ASTNodeWrapper<ASTInitializerClause>();
		operand1=new ASTNodeWrapper<ASTExpression>();
		operand2=new ASTNodeWrapper<ASTExpression>();
	}

	public ASTInitializerClause getInitOperand2(){
		return initOperand2.get();
	}

	public void setInitOperand2(ASTInitializerClause b){
		initOperand2.set(b);
	}

	public ASTExpression getOperand1(){
		return operand1.get();
	}

	public void setOperand1(ASTExpression b){
		operand1.set(b);
	}

	public ASTExpression getOperand2(){
		return operand2.get();
	}

	public void setOperand2(ASTExpression b){
		operand2.set(b);
	}

	public static String getOperator(int i){
		if (i==IASTBinaryExpression.op_assign){
			return "op_assign";
		}else if (i==IASTBinaryExpression.op_binaryAnd){
			return "op_binaryAnd";
		}else if (i==IASTBinaryExpression.op_binaryAndAssign){
			return "op_binaryAndAssign";
		}else if (i==IASTBinaryExpression.op_binaryOr){
			return "op_binaryOr";
		}else if (i==IASTBinaryExpression.op_binaryOrAssign){
			return "op_binaryOrAssign";
		}else if (i==IASTBinaryExpression.op_binaryXor){
			return "op_binaryXor";
		}else if (i==IASTBinaryExpression.op_binaryXorAssign){
			return "op_binaryXorAssign";
		}else if (i==IASTBinaryExpression.op_divide){
			return "op_divide";
		}else if (i==IASTBinaryExpression.op_divideAssign){
			return "op_divideAssign";
		}else if (i==IASTBinaryExpression.op_ellipses){
			return "op_ellipses";
		}else if (i==IASTBinaryExpression.op_equals){
			return "op_equals";
		}else if (i==IASTBinaryExpression.op_greaterEqual){
			return "op_greaterEqual";
		}else if (i==IASTBinaryExpression.op_greaterThan){
			return "op_greaterThan";
		}else if (i==IASTBinaryExpression.op_lessEqual){
			return "op_lessEqual";
		}else if (i==IASTBinaryExpression.op_lessThan){
			return "op_lessThan";
		}else if (i==IASTBinaryExpression.op_logicalAnd){
			return "op_logicalAnd";
		}else if (i==IASTBinaryExpression.op_logicalOr){
			return "op_logicalOr";
		}else if (i==IASTBinaryExpression.op_max){
			return "op_max";
		}else if (i==IASTBinaryExpression.op_min){
			return "op_min";
		}else if (i==IASTBinaryExpression.op_minus){
			return "op_minus";
		}else if (i==IASTBinaryExpression.op_minusAssign){
			return "op_minusAssign";
		}else if (i==IASTBinaryExpression.op_modulo){
			return "op_modulo";
		}else if (i==IASTBinaryExpression.op_moduloAssign){
			return "op_moduloAssign";
		}else if (i==IASTBinaryExpression.op_multiply){
			return "op_multiply";
		}else if (i==IASTBinaryExpression.op_multiplyAssign){
			return "op_multiplyAssign";
		}else if (i==IASTBinaryExpression.op_notequals){
			return "op_notequals";
		}else if (i==IASTBinaryExpression.op_plus){
			return "op_plus";
		}else if (i==IASTBinaryExpression.op_plusAssign){
			return "op_plusAssign";
		}else if (i==IASTBinaryExpression.op_pmarrow){
			return "op_pmarrow";
		}else if (i==IASTBinaryExpression.op_pmdot){
			return "op_pmdot";
		}else if (i==IASTBinaryExpression.op_shiftLeft){
			return "op_shiftLeft";
		}else if (i==IASTBinaryExpression.op_shiftLeftAssign){
			return "op_shiftLeftAssign";
		}else if (i==IASTBinaryExpression.op_shiftRight){
			return "op_shiftRight";
		}else if (i==IASTBinaryExpression.op_shiftRightAssign){
			return "op_shiftRightAssign";
		}else{
			return "unknown";
		}
	}

	public String getOperator(){
		return operator;
	}

	public void setOperator(String s){
		operator=s;
	}
}
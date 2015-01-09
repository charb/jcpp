package jcpp.model.cpp.ast.expr;

import jcpp.model.cpp.ast.expr.cpp.*;
import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.expr.init.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import jcpp.model.cpp.ast.id.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCastExpression extends ASTExpression{
	@XmlElement
	private ASTNodeWrapper<ASTExpression> operand;
	@XmlElement
	private String operator;
	@XmlElement
	private ASTNodeWrapper<ASTTypeId> typeId;

	public ASTCastExpression(IASTCastExpression expr) throws Exception{
		super(expr);
		operand=new ASTNodeWrapper<ASTExpression>();
		if (expr.getOperand()!=null){
			operand.set(ASTExpressionFactory.create(expr.getOperand()));
		}

		operator=getOperator(expr.getOperator());

		typeId=new ASTNodeWrapper<ASTTypeId>();
		if (expr.getTypeId()!=null){
			typeId.set(ASTTypeIdFactory.create(expr.getTypeId()));
		}
	}

	public ASTCastExpression(){
		operand=new ASTNodeWrapper<ASTExpression>();
		typeId=new ASTNodeWrapper<ASTTypeId>();
	}

	public ASTExpression getOperand(){
		return operand.get();
	}

	public void setOperand(ASTExpression b){
		operand.set(b);
	}

	public static String getOperator(int i){
		if (i==IASTCastExpression.op_cast){
			return "op_cast";
		}else if (i==ICPPASTCastExpression.op_const_cast){
			return "op_const_cast";
		}else if (i==ICPPASTCastExpression.op_dynamic_cast){
			return "op_dynamic_cast";
		}else if (i==ICPPASTCastExpression.op_reinterpret_cast){
			return "op_reinterpret_cast";
		}else if (i==ICPPASTCastExpression.op_static_cast){
			return "op_static_cast";
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

	public ASTTypeId getTypeId(){
		return typeId.get();
	}

	public void setTypeId(ASTTypeId b){
		typeId.set(b);
	}
}
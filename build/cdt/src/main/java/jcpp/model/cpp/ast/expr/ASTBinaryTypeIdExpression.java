package jcpp.model.cpp.ast.expr;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.expr.init.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import jcpp.model.cpp.ast.id.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTBinaryTypeIdExpression extends ASTExpression{
	@XmlElement
	private ASTNodeWrapper<ASTTypeId> operand1;
	@XmlElement
	private ASTNodeWrapper<ASTTypeId> operand2;
	@XmlElement
	private String operator;

	public ASTBinaryTypeIdExpression(IASTBinaryTypeIdExpression expr) throws Exception{
		super(expr);
		operand1=new ASTNodeWrapper<ASTTypeId>();
		if (expr.getOperand1()!=null){
			operand1.set(ASTTypeIdFactory.create(expr.getOperand1()));
		}

		operand2=new ASTNodeWrapper<ASTTypeId>();
		if (expr.getOperand2()!=null){
			operand2.set(ASTTypeIdFactory.create(expr.getOperand2()));
		}
		operator=expr.getOperator().toString();
	}

	public ASTBinaryTypeIdExpression(){
		operand1=new ASTNodeWrapper<ASTTypeId>();
		operand2=new ASTNodeWrapper<ASTTypeId>();
	}

	public ASTTypeId getOperand1(){
		return operand1.get();
	}

	public void setOperand1(ASTTypeId b){
		operand1.set(b);
	}

	public ASTTypeId getOperand2(){
		return operand2.get();
	}

	public void setOperand2(ASTTypeId b){
		operand2.set(b);
	}

	public String getOperator(){
		return operator;
	}

	public void setOperator(String b){
		operator=b;
	}
}
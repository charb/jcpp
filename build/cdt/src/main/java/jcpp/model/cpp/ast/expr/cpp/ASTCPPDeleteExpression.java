package jcpp.model.cpp.ast.expr.cpp;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.name.*;
import jcpp.model.cpp.ast.expr.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPDeleteExpression extends ASTCPPExpression{
	@XmlElement
	private ASTNodeWrapper<ASTExpression> operand;
	@XmlElement
	private boolean global;
	@XmlElement
	private boolean vectored;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTImplicitName> implicitNames;

	public ASTCPPDeleteExpression(ICPPASTDeleteExpression expr) throws Exception{
		super(expr);
		operand=new ASTNodeWrapper<ASTExpression>();
		if (expr.getOperand()!=null){
			operand.set(ASTExpressionFactory.create(expr.getOperand()));
		}
		global=expr.isGlobal();
		vectored=expr.isVectored();

		implicitNames=new ArrayList<ASTImplicitName>();
		if (expr.getImplicitNames()!=null){
			for (IASTImplicitName n : expr.getImplicitNames()){
				implicitNames.add((ASTImplicitName)ASTNameFactory.create(n));
			}
		}
	}

	public ASTCPPDeleteExpression(){
		operand=new ASTNodeWrapper<ASTExpression>();
	}

	public ASTExpression getOperand(){
		return operand.get();
	}

	public void setOperand(ASTExpression b){
		operand.set(b);
	}

	public boolean isGlobal(){
		return global;
	}

	public void setGlobal(boolean b){
		global=b;
	}

	public boolean isVectored(){
		return vectored;
	}

	public void setIsVectored(boolean b){
		vectored=b;
	}

	public List<ASTImplicitName> getImplicitNames(){
		return implicitNames;
	}

	public void addImplicitName(ASTImplicitName n){
		implicitNames.add(n);
	}
}
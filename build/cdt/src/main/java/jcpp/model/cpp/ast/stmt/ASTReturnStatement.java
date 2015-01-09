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
public class ASTReturnStatement extends ASTStatement{
	@XmlElement
	private ASTNodeWrapper<ASTInitializerClause> returnArgument;
	@XmlElement
	private ASTNodeWrapper<ASTExpression> returnValue;

	public ASTReturnStatement(IASTReturnStatement s) throws Exception{
		super(s);
		returnArgument=new ASTNodeWrapper<ASTInitializerClause>();
		if (s.getReturnArgument()!=null){
			returnArgument.set(ASTInitializerClauseFactory.create(s.getReturnArgument()));
		}

		returnValue=new ASTNodeWrapper<ASTExpression>();
		if (s.getReturnValue()!=null){
			returnValue.set(ASTExpressionFactory.create(s.getReturnValue()));
		}
	}

	public ASTReturnStatement(){
		returnArgument=new ASTNodeWrapper<ASTInitializerClause>();
		returnValue=new ASTNodeWrapper<ASTExpression>();
	}

	public ASTInitializerClause getReturnArgument(){
		return returnArgument.get();
	}

	public void setReturnArgument(ASTInitializerClause s){
		returnArgument.set(s);
	}

	public ASTExpression getReturnValue(){
		return returnValue.get();
	}

	public void setReturnValue(ASTExpression s){
		returnValue.set(s);
	}
}
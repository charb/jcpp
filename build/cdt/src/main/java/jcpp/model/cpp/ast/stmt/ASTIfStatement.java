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
public class ASTIfStatement extends ASTStatement{
	@XmlElement
	private ASTNodeWrapper<ASTExpression> conditionExpression;
	@XmlElement
	private ASTNodeWrapper<ASTStatement> thenClause;
	@XmlElement
	private ASTNodeWrapper<ASTStatement> elseClause;

	public ASTIfStatement(IASTIfStatement s) throws Exception{
		super(s);
		conditionExpression=new ASTNodeWrapper<ASTExpression>();
		if (s.getConditionExpression()!=null){
			conditionExpression.set(ASTExpressionFactory.create(s.getConditionExpression()));
		}

		thenClause=new ASTNodeWrapper<ASTStatement>();
		if (s.getThenClause()!=null){
			thenClause.set(ASTStatementFactory.create(s.getThenClause()));
		}

		elseClause=new ASTNodeWrapper<ASTStatement>();
		if (s.getElseClause()!=null){
			elseClause.set(ASTStatementFactory.create(s.getElseClause()));
		}
	}

	public ASTIfStatement(){
		conditionExpression=new ASTNodeWrapper<ASTExpression>();
		thenClause=new ASTNodeWrapper<ASTStatement>();
		elseClause=new ASTNodeWrapper<ASTStatement>();
	}

	public ASTExpression getConditionExpression(){
		return conditionExpression.get();
	}

	public void setConditionExpression(ASTExpression s){
		conditionExpression.set(s);
	}

	public ASTStatement getThenClause(){
		return thenClause.get();
	}

	public void setThenClause(ASTStatement s){
		thenClause.set(s);
	}

	public ASTStatement getElseClause(){
		return elseClause.get();
	}

	public void setElseClause(ASTStatement s){
		elseClause.set(s);
	}
}
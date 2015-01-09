package jcpp.model.cpp.ast.stmt;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.expr.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTForStatement extends ASTStatement{
	@XmlElement
	private ASTNodeWrapper<ASTStatement> body;
	@XmlElement
	private ASTNodeWrapper<ASTExpression> conditionExpression;
	@XmlElement
	private ASTNodeWrapper<ASTStatement> initializerStatement;
	@XmlElement
	private ASTNodeWrapper<ASTExpression> iterationExpression;

	public ASTForStatement(IASTForStatement s) throws Exception{
		super(s);
		body=new ASTNodeWrapper<ASTStatement>();
		if (s.getBody()!=null){
			body.set(ASTStatementFactory.create(s.getBody()));
		}

		conditionExpression=new ASTNodeWrapper<ASTExpression>();
		if (s.getConditionExpression()!=null){
			conditionExpression.set(ASTExpressionFactory.create(s.getConditionExpression()));
		}

		initializerStatement=new ASTNodeWrapper<ASTStatement>();
		if (s.getInitializerStatement()!=null){
			initializerStatement.set(ASTStatementFactory.create(s.getInitializerStatement()));
		}

		iterationExpression=new ASTNodeWrapper<ASTExpression>();
		if (s.getIterationExpression()!=null){
			iterationExpression.set(ASTExpressionFactory.create(s.getIterationExpression()));
		}
	}

	public ASTForStatement(){
		body=new ASTNodeWrapper<ASTStatement>();
		conditionExpression=new ASTNodeWrapper<ASTExpression>();
		initializerStatement=new ASTNodeWrapper<ASTStatement>();
		iterationExpression=new ASTNodeWrapper<ASTExpression>();
	}

	public ASTStatement getBody(){
		return body.get();
	}

	public void setBody(ASTStatement s){
		body.set(s);
	}

	public ASTExpression getConditionExpression(){
		return conditionExpression.get();
	}

	public void setConditionExpression(ASTExpression s){
		conditionExpression.set(s);
	}

	public ASTStatement getInitializerStatement(){
		return initializerStatement.get();
	}

	public void setInitializerStatement(ASTStatement s){
		initializerStatement.set(s);
	}

	public ASTExpression getIterationExpression(){
		return iterationExpression.get();
	}

	public void setIterationExpression(ASTExpression s){
		iterationExpression.set(s);
	}
}
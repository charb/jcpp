package jcpp.model.cpp.ast.stmt;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.expr.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTWhileStatement extends ASTStatement{
	@XmlElement
	private ASTNodeWrapper<ASTStatement> body;
	@XmlElement
	private ASTNodeWrapper<ASTExpression> condition;

	public ASTWhileStatement(IASTWhileStatement s) throws Exception{
		super(s);
		body=new ASTNodeWrapper<ASTStatement>();
		if (s.getBody()!=null){
			body.set(ASTStatementFactory.create(s.getBody()));
		}

		condition=new ASTNodeWrapper<ASTExpression>();
		if (s.getCondition()!=null){
			condition.set(ASTExpressionFactory.create(s.getCondition()));
		}
	}

	public ASTWhileStatement(){
		body=new ASTNodeWrapper<ASTStatement>();
		condition=new ASTNodeWrapper<ASTExpression>();
	}

	public ASTStatement getBody(){
		return body.get();
	}

	public void setBody(ASTStatement s){
		body.set(s);
	}

	public ASTExpression getCondition(){
		return condition.get();
	}

	public void setCondition(ASTExpression s){
		condition.set(s);
	}
}
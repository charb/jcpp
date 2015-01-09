package jcpp.model.cpp.ast.stmt;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.expr.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTExpressionStatement extends ASTStatement{
	@XmlElement
	private ASTNodeWrapper<ASTExpression> expression;

	public ASTExpressionStatement(IASTExpressionStatement s) throws Exception{
		super(s);
		expression=new ASTNodeWrapper<ASTExpression>();
		if (s.getExpression()!=null){
			expression.set(ASTExpressionFactory.create(s.getExpression()));
		}
	}

	public ASTExpressionStatement(){
		expression=new ASTNodeWrapper<ASTExpression>();
	}

	public ASTExpression getExpression(){
		return expression.get();
	}

	public void setExpression(ASTExpression s){
		expression.set(s);
	}
}
package jcpp.model.cpp.ast.expr;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.expr.init.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTExpressionList extends ASTExpression{
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTExpression> expressions;

	public ASTExpressionList(IASTExpressionList expr) throws Exception{
		super(expr);
		expressions=new ArrayList<ASTExpression>();
		if (expr.getExpressions()!=null){
			for (IASTExpression e : expr.getExpressions()){
				expressions.add(ASTExpressionFactory.create(e));
			}
		}
	}

	public ASTExpressionList(){
	}

	public List<ASTExpression> getExpressions(){
		return expressions;
	}

	public void addExpression(ASTExpression b){
		expressions.add(b);
	}
}
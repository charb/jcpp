package jcpp.model.cpp.ast.expr;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.expr.init.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTFunctionCallExpression extends ASTExpression{
	@XmlElement
	private ASTNodeWrapper<ASTExpression> functionNameExpression;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTInitializerClause> arguments;

	public ASTFunctionCallExpression(IASTFunctionCallExpression expr) throws Exception{
		super(expr);
		functionNameExpression=new ASTNodeWrapper<ASTExpression>();
		if (expr.getFunctionNameExpression()!=null){
			functionNameExpression.set(ASTExpressionFactory.create(expr.getFunctionNameExpression()));
		}
		
		arguments=new ArrayList<ASTInitializerClause>();
		if (expr.getArguments()!=null){
			for (IASTInitializerClause c : expr.getArguments()){
				arguments.add(ASTInitializerClauseFactory.create(c));
			}
		}
	}

	public ASTFunctionCallExpression(){
		functionNameExpression=new ASTNodeWrapper<ASTExpression>();
		arguments=new ArrayList<ASTInitializerClause>();
	}

	public void addArgument(ASTInitializerClause a){
		arguments.add(a);
	}

	public List<ASTInitializerClause> getArguments(){
		return arguments;
	}

	public ASTExpression getFunctionNameExpression(){
		return functionNameExpression.get();
	}

	public void setFunctionNameExpression(ASTExpression b){
		functionNameExpression.set(b);
	}
}
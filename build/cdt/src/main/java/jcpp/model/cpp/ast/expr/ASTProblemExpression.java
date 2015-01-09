package jcpp.model.cpp.ast.expr;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.name.*;
import jcpp.model.cpp.ast.expr.init.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTProblemExpression extends ASTExpression{
	@XmlElement
	private ASTNodeWrapper<ASTProblem> problem;

	public ASTProblemExpression(IASTProblemExpression expr) throws Exception{
		super(expr);
		problem=new ASTNodeWrapper<ASTProblem>();
		problem.set(new ASTProblem(expr.getProblem()));
	}

	public ASTProblemExpression(){
		problem=new ASTNodeWrapper<ASTProblem>();

	}

	public ASTProblem getProblem(){
		return problem.get();
	}

	public void setProblem(ASTProblem b){
		problem.set(b);
	}
}
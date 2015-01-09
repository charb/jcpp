package jcpp.model.cpp.ast.expr.cpp;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.expr.init.*;
import jcpp.model.cpp.ast.expr.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPPackExpansionExpression extends ASTCPPExpression{
	@XmlElement
	private ASTNodeWrapper<ASTExpression> pattern;

	public ASTCPPPackExpansionExpression(ICPPASTPackExpansionExpression e) throws Exception{
		super(e);
		pattern=new ASTNodeWrapper<ASTExpression>();
		if (e.getPattern()!=null){
			pattern.set(ASTExpressionFactory.create(e.getPattern()));
		}
	}

	public ASTCPPPackExpansionExpression(){
		pattern=new ASTNodeWrapper<ASTExpression>();
	}

	public ASTExpression getPattern(){
		return pattern.get();
	}

	public void setPattern(ASTExpression p){
		pattern.set(p);
	}
}
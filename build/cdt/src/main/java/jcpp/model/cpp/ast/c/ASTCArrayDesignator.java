package jcpp.model.cpp.ast.c;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.attribute.*;
import jcpp.model.cpp.ast.expr.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.c.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCArrayDesignator extends ASTCDesignator{
	@XmlElement
	private ASTNodeWrapper<ASTExpression> subscriptExpression;

	public ASTCArrayDesignator(ICASTArrayDesignator p) throws Exception{
		super(p);
		subscriptExpression=new ASTNodeWrapper<ASTExpression>();
		if (p.getSubscriptExpression()!=null){
			subscriptExpression.set(ASTExpressionFactory.create(p.getSubscriptExpression()));
		}
	}

	public ASTCArrayDesignator(){
		subscriptExpression=new ASTNodeWrapper<ASTExpression>();
	}

	public ASTExpression getSubscriptExpression(){
		return subscriptExpression.get();
	}

	public void setSubscriptExpression(ASTExpression e){
		subscriptExpression.set(e);
	}
}
package jcpp.model.cpp.ast.declarator;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.name.*;
import jcpp.model.cpp.ast.attribute.*;
import jcpp.model.cpp.ast.ptr.*;
import jcpp.model.cpp.ast.expr.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTArrayModifier extends ASTAttributeOwner{
	@XmlElement
	private ASTNodeWrapper<ASTExpression> constantExpression;

	public ASTArrayModifier(IASTArrayModifier decl) throws Exception{
		super(decl);
		constantExpression=new ASTNodeWrapper<ASTExpression>();
		if (decl.getConstantExpression()!=null){
			constantExpression.set(ASTExpressionFactory.create(decl.getConstantExpression()));
		}
	}

	public ASTArrayModifier(){
		constantExpression=new ASTNodeWrapper<ASTExpression>();
	}

	public ASTExpression getConstantExpression(){
		return constantExpression.get();
	}

	public void setConstantExpression(ASTExpression e){
		constantExpression.set(e);
	}
}
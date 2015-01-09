package jcpp.model.cpp.ast.expr;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.name.*;
import jcpp.model.cpp.ast.expr.init.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTIdExpression extends ASTExpression{
	@XmlElement
	private ASTNodeWrapper<ASTName> name;

	public ASTIdExpression(IASTIdExpression expr) throws Exception{
		super(expr);
		name=new ASTNodeWrapper<ASTName>();
		if (expr.getName()!=null){
			name.set(ASTNameFactory.create(expr.getName()));
		}
	}

	public ASTIdExpression(){
		name=new ASTNodeWrapper<ASTName>();
	}

	public ASTName getName(){
		return name.get();
	}

	public void setName(ASTName b){
		name.set(b);
	}
}
package jcpp.model.cpp.ast.declaration;

import jcpp.model.cpp.ast.declaration.specifier.*;
import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.expr.*;
import jcpp.model.cpp.ast.name.*;
import jcpp.model.cpp.ast.declarator.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTEnumerator extends ASTNode{
	@XmlElement
	private ASTNodeWrapper<ASTName> name;
	@XmlElement
	private ASTNodeWrapper<ASTExpression> value;

	public ASTEnumerator(IASTEnumerationSpecifier.IASTEnumerator d) throws Exception{
		super(d);
		name=new ASTNodeWrapper<ASTName>();
		if (d.getName()!=null){
			name.set(ASTNameFactory.create(d.getName()));
		}

		value=new ASTNodeWrapper<ASTExpression>();
		if (d.getValue()!=null){
			value.set(ASTExpressionFactory.create(d.getValue()));
		}
	}

	public ASTEnumerator(){
		name=new ASTNodeWrapper<ASTName>();
		value=new ASTNodeWrapper<ASTExpression>();
	}

	public ASTName getName(){
		return name.get();
	}

	public void setName(ASTName d){
		name.set(d);
	}

	public ASTExpression getValue(){
		return value.get();
	}

	public void setValue(ASTExpression s){
		value.set(s);
	}
}
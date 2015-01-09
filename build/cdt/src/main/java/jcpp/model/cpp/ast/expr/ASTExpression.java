package jcpp.model.cpp.ast.expr;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.expr.init.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTExpression extends ASTInitializerClause{
	@XmlElement
	private String valueCategory;
	@XmlElement
	private boolean bIsLValue;

	public ASTExpression(IASTExpression e) throws Exception{
		super(e);
		valueCategory=e.getValueCategory().toString();
		bIsLValue=e.isLValue();
	}

	public ASTExpression(){
	}

	public String getValueCategory(){
		return valueCategory;
	}

	public void setValueCategory(String b){
		valueCategory=b;
	}

	public boolean isLValue(){
		return bIsLValue;
	}

	public void setLValue(boolean b){
		bIsLValue=b;
	}
}
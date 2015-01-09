package jcpp.model.cpp.ast.expr;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.name.*;
import jcpp.model.cpp.ast.expr.init.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTFieldReferenceExpression extends ASTExpression{
	@XmlElement
	private ASTNodeWrapper<ASTName> fieldName;
	@XmlElement
	private ASTNodeWrapper<ASTExpression> fieldOwner;
	@XmlElement
	private boolean bIsPointerDereference;

	public ASTFieldReferenceExpression(IASTFieldReference expr) throws Exception{
		super(expr);
		fieldName=new ASTNodeWrapper<ASTName>();
		if (expr.getFieldName()!=null){
			fieldName.set(ASTNameFactory.create(expr.getFieldName()));
		}

		fieldOwner=new ASTNodeWrapper<ASTExpression>();
		if (expr.getFieldOwner()!=null){
			fieldOwner.set(ASTExpressionFactory.create(expr.getFieldOwner()));
		}
		bIsPointerDereference=expr.isPointerDereference();
	}

	public ASTFieldReferenceExpression(){
		fieldName=new ASTNodeWrapper<ASTName>();
		fieldOwner=new ASTNodeWrapper<ASTExpression>();
	}

	public ASTName getFieldName(){
		return fieldName.get();
	}

	public void setFieldName(ASTName b){
		fieldName.set(b);
	}

	public ASTExpression getFieldOwner(){
		return fieldOwner.get();
	}

	public void setFieldOwner(ASTExpression b){
		fieldOwner.set(b);
	}

	public boolean isPointerDereference(){
		return bIsPointerDereference;
	}

	public void setIsPointerDereference(boolean b){
		bIsPointerDereference=b;
	}
}
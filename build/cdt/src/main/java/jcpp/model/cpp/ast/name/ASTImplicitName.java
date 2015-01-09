package jcpp.model.cpp.ast.name;

import jcpp.model.cpp.ast.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTImplicitName extends ASTName{
	@XmlAttribute
	private boolean bIsAlternate;
	@XmlAttribute
	private boolean bIsOperator;

	public ASTImplicitName(IASTImplicitName name) throws Exception{
		super(name);
		bIsAlternate=name.isAlternate();
		bIsOperator=name.isOperator();
	}

	public ASTImplicitName(){
	}

	public boolean isAlternate(){
		return bIsAlternate;
	}

	public void setIsAlternate(boolean b){
		bIsAlternate=b;
	}

	public boolean isOperator(){
		return bIsOperator;
	}

	public void setIsOperator(boolean b){
		bIsOperator=b;
	}
}
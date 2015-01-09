package jcpp.model.cpp.ast.attribute;

import jcpp.model.cpp.ast.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTAttribute extends ASTNode{
	@XmlElement
	private String name;

	public ASTAttribute(IASTAttribute decl) throws Exception{
		super(decl);
		name=new String(decl.getName());
	}

	public ASTAttribute(){
	}

	public String getName(){
		return name;
	}

	public void setName(String n){
		name=n;
	}
}
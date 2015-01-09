package jcpp.model.cpp.ast.macro;

import jcpp.model.cpp.ast.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTFunctionStyleMacroParameter extends ASTNode{
	@XmlElement
	private String parameter;

	public ASTFunctionStyleMacroParameter(IASTFunctionStyleMacroParameter p) throws Exception{
		super(p);
		parameter=p.getParameter();
	}

	public ASTFunctionStyleMacroParameter(){
	}

	public String getParameter(){
		return parameter;
	}

	public void setParameter(String p){
		parameter=p;
	}
}
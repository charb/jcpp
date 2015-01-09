package jcpp.model.cpp.ast.attribute.cpp;

import jcpp.model.cpp.ast.attribute.*;
import jcpp.model.cpp.ast.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPAttribute extends ASTAttribute{
	@XmlElement
	private String scope;
	@XmlElement
	private boolean bHasPackExpansion;

	public ASTCPPAttribute(ICPPASTAttribute decl) throws Exception{
		super(decl);
		scope=new String(decl.getScope());
		bHasPackExpansion=decl.hasPackExpansion();
	}

	public ASTCPPAttribute(){
	}

	public String getScope(){
		return scope;
	}

	public void setScope(String n){
		scope=n;
	}

	public boolean hasPackExpansion(){
		return bHasPackExpansion;
	}

	public void setHasPackExpansion(boolean b){
		bHasPackExpansion=b;
	}
}
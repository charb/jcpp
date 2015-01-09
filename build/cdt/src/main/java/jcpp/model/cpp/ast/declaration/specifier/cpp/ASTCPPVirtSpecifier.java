package jcpp.model.cpp.ast.declaration.specifier.cpp;

import jcpp.model.cpp.ast.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPVirtSpecifier extends ASTNode{
	@XmlElement
	private String kind;

	public ASTCPPVirtSpecifier(ICPPASTVirtSpecifier s) throws Exception{
		super(s);
		kind=s.getKind().toString();
	}

	public ASTCPPVirtSpecifier(){
	}

	public String getKind(){
		return kind;
	}

	public void setKind(String s){
		kind=s;
	}
}
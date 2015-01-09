package jcpp.model.cpp.ast.declaration.specifier.cpp;

import jcpp.model.cpp.ast.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPClassVirtSpecifier extends ASTNode{
	@XmlElement
	private String kind;

	public ASTCPPClassVirtSpecifier(ICPPASTClassVirtSpecifier s) throws Exception{
		super(s);
		kind=s.getKind().toString();
	}

	public ASTCPPClassVirtSpecifier(){
	}

	public String getKind(){
		return kind;
	}

	public void setKind(String s){
		kind=s;
	}
}
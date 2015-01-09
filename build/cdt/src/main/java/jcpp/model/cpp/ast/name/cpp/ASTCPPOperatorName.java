package jcpp.model.cpp.ast.name.cpp;

import jcpp.model.cpp.ast.name.*;
import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.location.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPOperatorName extends ASTCPPName{
	

	public ASTCPPOperatorName(ICPPASTOperatorName name) throws Exception{
		super(name);
	}

	public ASTCPPOperatorName(){
	}
}
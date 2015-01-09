package jcpp.model.cpp.ast.expr.cpp;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.expr.init.*;
import jcpp.model.cpp.ast.expr.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPExpression extends ASTExpression{

	public ASTCPPExpression(ICPPASTExpression e) throws Exception{
		super(e);
	}

	public ASTCPPExpression(){
	}
}
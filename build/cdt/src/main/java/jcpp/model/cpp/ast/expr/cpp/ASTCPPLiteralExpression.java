package jcpp.model.cpp.ast.expr.cpp;

import jcpp.model.cpp.ast.expr.*;
import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.expr.init.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPLiteralExpression extends ASTLiteralExpression{

	public ASTCPPLiteralExpression(ICPPASTLiteralExpression expr) throws Exception{
		super(expr);
	}

	public ASTCPPLiteralExpression(){
	}
}
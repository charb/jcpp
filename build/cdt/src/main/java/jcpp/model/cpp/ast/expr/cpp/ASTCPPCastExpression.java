package jcpp.model.cpp.ast.expr.cpp;

import jcpp.model.cpp.ast.expr.*;
import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.expr.init.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import jcpp.model.cpp.ast.id.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
//TODO remplacer type in par enum ou string
public class ASTCPPCastExpression extends ASTCastExpression{

	public ASTCPPCastExpression(ICPPASTCastExpression expr) throws Exception{
		super(expr);
	}

	public ASTCPPCastExpression(){
	}
}
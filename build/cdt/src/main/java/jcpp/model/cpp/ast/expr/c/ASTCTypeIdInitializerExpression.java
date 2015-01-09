package jcpp.model.cpp.ast.expr.c;

import jcpp.model.cpp.ast.expr.*;
import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.id.*;
import jcpp.model.cpp.ast.expr.init.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.c.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCTypeIdInitializerExpression extends ASTTypeIdInitializerExpression{

	public ASTCTypeIdInitializerExpression(ICASTTypeIdInitializerExpression expr) throws Exception{
		super(expr);
	}

	public ASTCTypeIdInitializerExpression(){
	}
}
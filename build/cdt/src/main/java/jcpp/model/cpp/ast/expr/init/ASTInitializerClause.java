package jcpp.model.cpp.ast.expr.init;

import jcpp.model.cpp.ast.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTInitializerClause extends ASTNode{

	public ASTInitializerClause(IASTInitializerClause init) throws Exception{
		super(init);
	}

	public ASTInitializerClause(){
	}
}
package jcpp.model.cpp.ast.expr.init;

import jcpp.model.cpp.ast.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTInitializer extends ASTNode{

	public ASTInitializer(IASTInitializer i) throws Exception{
		super(i);
	}

	public ASTInitializer(){
	}
}
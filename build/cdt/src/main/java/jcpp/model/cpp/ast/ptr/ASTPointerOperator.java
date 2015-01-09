package jcpp.model.cpp.ast.ptr;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.attribute.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTPointerOperator extends ASTAttributeOwner{

	public ASTPointerOperator(IASTPointerOperator p) throws Exception{
		super(p);
	}

	public ASTPointerOperator(){
	}
}
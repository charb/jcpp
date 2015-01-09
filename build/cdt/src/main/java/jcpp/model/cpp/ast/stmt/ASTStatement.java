package jcpp.model.cpp.ast.stmt;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.attribute.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTStatement extends ASTAttributeOwner{

	public ASTStatement(IASTStatement s) throws Exception{
		super(s);
	}

	public ASTStatement(){
	}
}
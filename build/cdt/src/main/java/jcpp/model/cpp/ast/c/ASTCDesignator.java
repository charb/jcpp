package jcpp.model.cpp.ast.c;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.attribute.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.c.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCDesignator extends ASTNode{

	public ASTCDesignator(ICASTDesignator p) throws Exception{
		super(p);
	}

	public ASTCDesignator(){
	}
}
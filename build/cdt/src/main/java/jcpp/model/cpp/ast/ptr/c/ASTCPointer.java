package jcpp.model.cpp.ast.ptr.c;

import jcpp.model.cpp.ast.ptr.*;
import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.attribute.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.c.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPointer extends ASTPointer{

	public ASTCPointer(ICASTPointer p) throws Exception{
		super(p);
	}

	public ASTCPointer(){
	}
}
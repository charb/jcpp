package jcpp.model.cpp.ast.declarator;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.name.*;
import jcpp.model.cpp.ast.ptr.*;
import jcpp.model.cpp.ast.expr.init.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTFunctionDeclarator extends ASTDeclarator{

	public ASTFunctionDeclarator(IASTFunctionDeclarator decl) throws Exception{
		super(decl);
	}

	public ASTFunctionDeclarator(){
	}
}
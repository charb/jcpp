package jcpp.model.cpp.ast.declaration.specifier.c;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.declaration.specifier.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.c.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCDeclSpecifier extends ASTDeclSpecifier{

	public ASTCDeclSpecifier(ICASTDeclSpecifier s) throws Exception{
		super(s);
	}

	public ASTCDeclSpecifier(){
	}
}
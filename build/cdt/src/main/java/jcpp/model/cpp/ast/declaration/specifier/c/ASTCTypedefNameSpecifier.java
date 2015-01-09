package jcpp.model.cpp.ast.declaration.specifier.c;

import jcpp.model.cpp.ast.declaration.specifier.*;
import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.declaration.*;
import jcpp.model.cpp.ast.name.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.c.*;
import java.util.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCTypedefNameSpecifier extends ASTNamedTypeSpecifier{

	public ASTCTypedefNameSpecifier(ICASTTypedefNameSpecifier s) throws Exception{
		super(s);
	}

	public ASTCTypedefNameSpecifier(){
	}

}
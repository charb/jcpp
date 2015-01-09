package jcpp.model.cpp.ast.location;

import org.eclipse.cdt.core.dom.ast.*;
import jcpp.model.cpp.ast.macro.*;
import javax.xml.bind.annotation.*;
import jcpp.model.cpp.ast.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTMacroExpansionLocation extends ASTNodeLocation{

	public ASTMacroExpansionLocation(IASTMacroExpansionLocation location) throws Exception{
		super(location);
	}

	public ASTMacroExpansionLocation(){
	}
}
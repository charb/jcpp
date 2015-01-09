package jcpp.model.cpp.ast.id.cpp;

import jcpp.model.cpp.ast.id.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.declarator.*;
import jcpp.model.cpp.ast.declaration.specifier.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPTypeId extends ASTTypeId{
	@XmlElement
	private boolean packExpansion;

	public ASTCPPTypeId(ICPPASTTypeId typeId) throws Exception{
		super(typeId);
		packExpansion=typeId.isPackExpansion();
	}

	public ASTCPPTypeId(){
	}

	public boolean isPackExpansion(){
		return packExpansion;
	}

	public void setIsPackExpansion(boolean d){
		packExpansion=d;
	}
}
package jcpp.model.cpp.ast.ptr.cpp;

import jcpp.model.cpp.ast.ptr.*;
import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.name.*;
import jcpp.model.cpp.ast.attribute.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPPointerToMember extends ASTPointer{
	@XmlElement
	private ASTNodeWrapper<ASTName> name;

	public ASTCPPPointerToMember(ICPPASTPointerToMember p) throws Exception{
		super(p);
		name=new ASTNodeWrapper<ASTName>();
		if (p.getName()!=null){
			name.set(ASTNameFactory.create(p.getName()));
		}
	}

	public ASTCPPPointerToMember(){
		name=new ASTNodeWrapper<ASTName>();
	}

	public ASTName getName(){
		return name.get();
	}

	public void setName(ASTName n){
		name.set(n);
	}

}
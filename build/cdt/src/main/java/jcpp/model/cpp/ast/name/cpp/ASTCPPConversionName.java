package jcpp.model.cpp.ast.name.cpp;

import jcpp.model.cpp.ast.name.*;
import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.id.*;
import jcpp.model.cpp.ast.location.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPConversionName extends ASTCPPName{
	@XmlElement
	private ASTNodeWrapper<ASTTypeId> typeId;

	public ASTCPPConversionName(ICPPASTConversionName name) throws Exception{
		super(name);
		typeId=new ASTNodeWrapper<ASTTypeId>();
		if (name.getTypeId()!=null){
			typeId.set(ASTTypeIdFactory.create(name.getTypeId()));
		}
	}

	public ASTCPPConversionName(){
		typeId=new ASTNodeWrapper<ASTTypeId>();
	}

	public ASTTypeId getTypeId(){
		return typeId.get();
	}

	public void setTypeId(ASTTypeId i){
		typeId.set(i);
	}
}
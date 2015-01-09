package jcpp.model.cpp.ast.cpp;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.attribute.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPTemplateParameter extends ASTNode{
	@XmlElement
	private boolean bIsParameterPack;

	public ASTCPPTemplateParameter(ICPPASTTemplateParameter p) throws Exception{
		super(p);
		bIsParameterPack=p.isParameterPack();
	}

	public ASTCPPTemplateParameter(){
	}

	public boolean isParameterPack(){
		return bIsParameterPack;
	}

	public void setIsParameterPack(boolean b){
		bIsParameterPack=b;
	}
}
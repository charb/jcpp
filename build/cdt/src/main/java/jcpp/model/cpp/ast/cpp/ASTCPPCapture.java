package jcpp.model.cpp.ast.cpp;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.name.*;
import jcpp.model.cpp.ast.attribute.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPCapture extends ASTNode{
	@XmlElement
	private boolean bIsByReference;
	@XmlElement
	private boolean bCapturesThisPointer;
	@XmlElement
	private ASTNodeWrapper<ASTName> identifier;
	@XmlElement
	private boolean packExpansion;

	public ASTCPPCapture(ICPPASTCapture p) throws Exception{
		super(p);
		bIsByReference=p.isByReference();
		bCapturesThisPointer=p.capturesThisPointer();
		identifier=new ASTNodeWrapper<ASTName>();
		if (p.getIdentifier()!=null){
			identifier.set(ASTNameFactory.create(p.getIdentifier()));
		}
		packExpansion=p.isPackExpansion();
	}

	public ASTCPPCapture(){
		identifier=new ASTNodeWrapper<ASTName>();
	}

	public boolean isByReference(){
		return bIsByReference;
	}

	public void setIsByReference(boolean b){
		bIsByReference=b;
	}

	public boolean capturesThisPointer(){
		return bCapturesThisPointer;
	}

	public void setCapturesThisPointer(boolean b){
		bCapturesThisPointer=b;
	}

	public ASTName getIdentifier(){
		return identifier.get();
	}

	public void setIdentifier(ASTName n){
		identifier.set(n);
	}

	public boolean isPackExpansion(){
		return packExpansion;
	}

	public void setIsPackExpansion(boolean d){
		packExpansion=d;
	}
}
package jcpp.model.cpp.ast.ptr;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.attribute.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTPointer extends ASTPointerOperator{
	@XmlElement
	private boolean bIsConst;
	@XmlElement
	private boolean bIsRestrict;
	@XmlElement
	private boolean bIsVolatile; 

	public ASTPointer(IASTPointer p) throws Exception{
		super(p);
		bIsConst=p.isConst();
		bIsRestrict=p.isRestrict();
		bIsVolatile=p.isVolatile();
	}

	public ASTPointer(){
	}

	public boolean isConst(){
		return bIsConst;
	}

	public void setIsConst(boolean b){
		bIsConst=b;
	}

	public boolean isRestrict(){
		return bIsRestrict;
	}

	public void setIsRestrict(boolean b){
		bIsRestrict=b;
	}

	public boolean isVolatile(){
		return bIsVolatile;
	}

	public void setIsVolatile(boolean b){
		bIsVolatile=b;
	}
}
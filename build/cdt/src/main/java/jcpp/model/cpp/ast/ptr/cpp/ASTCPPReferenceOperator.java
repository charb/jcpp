package jcpp.model.cpp.ast.ptr.cpp;

import jcpp.model.cpp.ast.ptr.*;
import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.attribute.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import java.util.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPReferenceOperator extends ASTPointerOperator{
	@XmlElement
	private boolean bIsRValueReference;

	public ASTCPPReferenceOperator(ICPPASTReferenceOperator p) throws Exception{
		super(p);
		bIsRValueReference=p.isRValueReference();

	}

	public ASTCPPReferenceOperator(){
	}

	public boolean isRValueReference(){
		return bIsRValueReference;
	}

	public void setIsRValueReference(boolean b){
		bIsRValueReference=b;
	}
}
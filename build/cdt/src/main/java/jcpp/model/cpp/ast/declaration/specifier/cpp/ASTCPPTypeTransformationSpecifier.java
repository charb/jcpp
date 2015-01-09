package jcpp.model.cpp.ast.declaration.specifier.cpp;

import jcpp.model.cpp.ast.declaration.specifier.*;
import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.id.*;
import jcpp.model.cpp.ast.attribute.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import java.util.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPTypeTransformationSpecifier extends ASTCPPDeclSpecifier{
	@XmlElement
	private ASTNodeWrapper<ASTTypeId> operand;
	@XmlElement
	private String operator;

	public ASTCPPTypeTransformationSpecifier(ICPPASTTypeTransformationSpecifier s) throws Exception{
		super(s);
		operand=new ASTNodeWrapper<ASTTypeId>();
		if (s.getOperand()!=null){
			operand.set(ASTTypeIdFactory.create(s.getOperand()));
		}
		operator=s.getOperator().toString();
	}

	public ASTCPPTypeTransformationSpecifier(){
		operand=new ASTNodeWrapper<ASTTypeId>();
	}
	
	public ASTTypeId getOperand(){
		return operand.get();
	}

	public void setOperand(ASTTypeId b){
		operand.set(b);
	}

	public String getOperator(){
		return operator;
	}

	public void setOperator(String b){
		operator=b;
	}
}
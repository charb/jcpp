package jcpp.model.cpp.ast.id;

import org.eclipse.cdt.core.dom.ast.*;
import jcpp.model.cpp.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTProblemTypeId extends ASTTypeId{
	@XmlElement
	private ASTNodeWrapper<ASTProblem> problem;

	public ASTProblemTypeId(IASTProblemTypeId typeId) throws Exception{
		super(typeId);
		problem=new ASTNodeWrapper<ASTProblem>();
		problem.set(new ASTProblem(typeId.getProblem()));
	}

	public ASTProblemTypeId(){
		problem=new ASTNodeWrapper<ASTProblem>();
	}

	public ASTProblem getProblem(){
		return problem.get();
	}

	public void setProblem(ASTProblem p){
		problem.set(p);
	}
}
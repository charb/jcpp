package jcpp.model.cpp.ast.stmt;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.expr.*;
import jcpp.model.cpp.ast.expr.init.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTProblemStatement extends ASTStatement{
	@XmlElement
	private ASTNodeWrapper<ASTProblem> problem;

	public ASTProblemStatement(IASTProblemStatement s) throws Exception{
		super(s);
		problem=new ASTNodeWrapper<ASTProblem>();
		problem.set(new ASTProblem(s.getProblem()));
	}

	public ASTProblemStatement(){
		problem=new ASTNodeWrapper<ASTProblem>();
	}

	public ASTProblem getProblem(){
		return problem.get();
	}

	public void setProblem(ASTProblem s){
		problem.set(s);
	}
}
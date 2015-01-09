package jcpp.model.cpp.ast.declaration;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.stmt.*;
import jcpp.model.cpp.ast.declarator.*;
import jcpp.model.cpp.ast.declaration.specifier.*;
import org.eclipse.cdt.core.dom.ast.*;
import java.util.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTProblemDeclaration extends ASTDeclaration{
	@XmlElement
	private ASTNodeWrapper<ASTProblem> problem;

	public ASTProblemDeclaration(IASTProblemDeclaration d) throws Exception{
		super(d);
		problem=new ASTNodeWrapper<ASTProblem>();
		problem.set(new ASTProblem(d.getProblem()));
	}

	public ASTProblemDeclaration(){
		problem=new ASTNodeWrapper<ASTProblem>();
	}

	public ASTProblem getProblem(){
		return problem.get();
	}

	public void setProblem(ASTProblem a){
		problem.set(a);
	}
}
package jcpp.model.cpp.ast.expr.init.cpp;

import jcpp.model.cpp.ast.expr.init.*;
import jcpp.model.cpp.ast.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import java.util.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPConstructorInitializer extends ASTInitializer{
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTInitializerClause> arguments;

	public ASTCPPConstructorInitializer(ICPPASTConstructorInitializer init) throws Exception{
		super(init);
		arguments=new ArrayList<ASTInitializerClause>();
		if (init.getArguments()!=null){
			for (IASTInitializerClause c : init.getArguments()){
				arguments.add(ASTInitializerClauseFactory.create(c));
			}
		}
	}

	public ASTCPPConstructorInitializer(){
	}

	public List<ASTInitializerClause> getArguments(){
		return arguments;
	}

	public void addArgument(ASTInitializerClause c){
		arguments.add(c);
	}
}
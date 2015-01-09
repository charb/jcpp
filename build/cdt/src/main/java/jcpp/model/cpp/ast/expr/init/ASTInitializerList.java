package jcpp.model.cpp.ast.expr.init;

import jcpp.model.cpp.ast.*;
import org.eclipse.cdt.core.dom.ast.*;
import java.util.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTInitializerList extends ASTInitializer{
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTInitializerClause> clauses;

	public ASTInitializerList(IASTInitializerList i) throws Exception{
		super(i);
		clauses=new ArrayList<ASTInitializerClause>();
		if (i.getClauses()!=null){
			for (IASTInitializerClause c : i.getClauses()){
				clauses.add(ASTInitializerClauseFactory.create(c));
			}
		}
	}

	public ASTInitializerList(){
	}

	public List<ASTInitializerClause> getClauses(){
		return clauses;
	}

	public void addClause(ASTInitializerClause c){
		clauses.add(c);
	}
}
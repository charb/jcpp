package jcpp.model.cpp.ast.stmt;

import jcpp.model.cpp.ast.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCompoundStatement extends ASTStatement{
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTStatement> statements;

	public ASTCompoundStatement(IASTCompoundStatement s) throws Exception{
		super(s);
		statements=new ArrayList<ASTStatement>();
		if (s.getStatements()!=null){
			for (IASTStatement s1 : s.getStatements()){
				statements.add(ASTStatementFactory.create(s1));
			}
		}
	}

	public ASTCompoundStatement(){
	}

	public List<ASTStatement> getStatements(){
		return statements;
	}

	public void addStatement(ASTStatement s){
		statements.add(s);
	}
}
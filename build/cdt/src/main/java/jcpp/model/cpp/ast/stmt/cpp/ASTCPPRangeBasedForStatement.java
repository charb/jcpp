package jcpp.model.cpp.ast.stmt;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.expr.*;
import jcpp.model.cpp.ast.name.*;
import jcpp.model.cpp.ast.expr.init.*;
import jcpp.model.cpp.ast.declaration.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPRangeBasedForStatement extends ASTStatement{
	@XmlElement
	private ASTNodeWrapper<ASTStatement> body;
	@XmlElement
	private ASTNodeWrapper<ASTDeclaration> declaration;
	@XmlElement
	private ASTNodeWrapper<ASTInitializerClause> initializerClause;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTImplicitName> implicitNames;

	public ASTCPPRangeBasedForStatement(ICPPASTRangeBasedForStatement s) throws Exception{
		super(s);
		body=new ASTNodeWrapper<ASTStatement>();
		if (s.getBody()!=null){
			body.set(ASTStatementFactory.create(s.getBody()));
		}

		declaration=new ASTNodeWrapper<ASTDeclaration>();
		if (s.getDeclaration()!=null){
			declaration.set((ASTDeclaration)ASTDeclarationFactory.create(s.getDeclaration()));
		}

		initializerClause=new ASTNodeWrapper<ASTInitializerClause>();
		if (s.getInitializerClause()!=null){
			initializerClause.set(ASTInitializerClauseFactory.create(s.getInitializerClause()));
		}
		
		implicitNames=new ArrayList<ASTImplicitName>();
		if (s.getImplicitNames()!=null){
			for (IASTImplicitName n : s.getImplicitNames()){
				implicitNames.add((ASTImplicitName)ASTNameFactory.create(n));
			}
		}
	}

	public ASTCPPRangeBasedForStatement(){
		body=new ASTNodeWrapper<ASTStatement>();
		declaration=new ASTNodeWrapper<ASTDeclaration>();
		initializerClause=new ASTNodeWrapper<ASTInitializerClause>();
	}

	public ASTStatement getBody(){
		return body.get();
	}

	public void setBody(ASTStatement s){
		body.set(s);
	}

	public ASTDeclaration getDeclaration(){
		return declaration.get();
	}

	public void setDeclaration(ASTDeclaration s){
		declaration.set(s);
	}

	public ASTInitializerClause getInitializerClause(){
		return initializerClause.get();
	}

	public void setInitializerClause(ASTInitializerClause s){
		initializerClause.set(s);
	}

	public List<ASTImplicitName> getImplicitNames(){
		return implicitNames;
	}

	public void addImplicitName(ASTImplicitName n){
		implicitNames.add(n);
	}
}
package jcpp.model.cpp.ast.stmt.cpp;

import jcpp.model.cpp.ast.stmt.*;
import jcpp.model.cpp.ast.declaration.*;
import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.expr.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPCatchHandler extends ASTStatement{
	@XmlElement
	private boolean bIsCatchAll;
	@XmlElement
	private ASTNodeWrapper<ASTStatement> catchBody;
	@XmlElement
	private ASTNodeWrapper<ASTDeclaration> declaration;

	public ASTCPPCatchHandler(ICPPASTCatchHandler s) throws Exception{
		super(s);
		bIsCatchAll=s.isCatchAll();

		catchBody=new ASTNodeWrapper<ASTStatement>();
		if (s.getCatchBody()!=null){
			catchBody.set(ASTStatementFactory.create(s.getCatchBody()));
		}

		declaration=new ASTNodeWrapper<ASTDeclaration>();
		if (s.getDeclaration()!=null){
			declaration.set((ASTDeclaration)ASTDeclarationFactory.create(s.getDeclaration()));
		}
	}

	public ASTCPPCatchHandler(){
		catchBody=new ASTNodeWrapper<ASTStatement>();
		declaration=new ASTNodeWrapper<ASTDeclaration>();
	}

	public boolean isCatchAll(){
		return bIsCatchAll;
	}

	public void setIsCatchAll(boolean s){
		bIsCatchAll=s;
	}

	public ASTStatement getCatchBody(){
		return catchBody.get();
	}

	public void setCatchBody(ASTStatement s){
		catchBody.set(s);
	}

	public ASTDeclaration getDeclaration(){
		return declaration.get();
	}

	public void setDeclaration(ASTDeclaration s){
		declaration.set(s);
	}
}
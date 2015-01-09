package jcpp.model.cpp.ast.stmt.cpp;

import jcpp.model.cpp.ast.stmt.*;
import jcpp.model.cpp.ast.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPTryBlockStatement extends ASTStatement{
	@XmlElement
	private ASTNodeWrapper<ASTStatement> tryBody;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTCPPCatchHandler> catchHandlers;

	public ASTCPPTryBlockStatement(ICPPASTTryBlockStatement s) throws Exception{
		super(s);
		catchHandlers=new ArrayList<ASTCPPCatchHandler>();
		if (s.getCatchHandlers()!=null){
			for (ICPPASTCatchHandler s1 : s.getCatchHandlers()){
				catchHandlers.add((ASTCPPCatchHandler)ASTStatementFactory.create(s1));
			}
		}

		tryBody=new ASTNodeWrapper<ASTStatement>();	
		if (s.getTryBody()!=null){
			tryBody.set(ASTStatementFactory.create(s.getTryBody()));
		}
	}

	public ASTCPPTryBlockStatement(){
		tryBody=new ASTNodeWrapper<ASTStatement>();	
	}

	public List<ASTCPPCatchHandler> getCatchHandlers(){
		return catchHandlers;
	}

	public void addCatchHandler(ASTCPPCatchHandler s){
		catchHandlers.add(s);
	}

	public ASTStatement getTryBody(){
		return tryBody.get();
	}

	public void setTryBody(ASTStatement s){
		tryBody.set(s);
	}
}
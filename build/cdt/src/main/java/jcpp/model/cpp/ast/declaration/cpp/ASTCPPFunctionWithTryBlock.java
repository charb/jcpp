package jcpp.model.cpp.ast.declaration.cpp;

import jcpp.model.cpp.ast.declaration.*;
import jcpp.model.cpp.ast.expr.init.*;
import jcpp.model.cpp.ast.expr.init.cpp.*;
import jcpp.model.cpp.ast.name.*;
import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.declarator.*;
import jcpp.model.cpp.ast.stmt.cpp.*;
import jcpp.model.cpp.ast.stmt.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import java.util.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPFunctionWithTryBlock extends ASTCPPFunctionDefinition{
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTCPPCatchHandler> catchHandlers;

	public ASTCPPFunctionWithTryBlock(ICPPASTFunctionWithTryBlock d) throws Exception{
		super(d);
		catchHandlers=new ArrayList<ASTCPPCatchHandler>();
		if (d.getCatchHandlers()!=null){
			for (ICPPASTCatchHandler ci : d.getCatchHandlers()){
				catchHandlers.add((ASTCPPCatchHandler)ASTStatementFactory.create(ci));
			}
		}
	}

	public ASTCPPFunctionWithTryBlock(){
	}

	public List<ASTCPPCatchHandler> getCatchHandlers(){
		return catchHandlers;
	}

	public void addCatchHandler(ASTCPPCatchHandler c){
		catchHandlers.add(c);
	}
}
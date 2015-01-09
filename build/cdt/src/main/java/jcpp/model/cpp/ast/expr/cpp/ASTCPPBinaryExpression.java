package jcpp.model.cpp.ast.expr.cpp;

import jcpp.model.cpp.ast.expr.*;
import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.expr.init.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import jcpp.model.cpp.ast.name.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPBinaryExpression extends ASTBinaryExpression{
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTImplicitName> implicitNames;

	public ASTCPPBinaryExpression(ICPPASTBinaryExpression expr) throws Exception{
		super(expr);
		implicitNames=new ArrayList<ASTImplicitName>();
		if (expr.getImplicitNames()!=null){
			for (IASTImplicitName n : expr.getImplicitNames()){
				implicitNames.add((ASTImplicitName)ASTNameFactory.create(n));
			}
		}
	}

	public ASTCPPBinaryExpression(){
	}

	public List<ASTImplicitName> getImplicitNames(){
		return implicitNames;
	}

	public void addImplicitName(ASTImplicitName n){
		implicitNames.add(n);
	}
}
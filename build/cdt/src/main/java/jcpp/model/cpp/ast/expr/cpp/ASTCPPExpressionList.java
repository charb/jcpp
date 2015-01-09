package jcpp.model.cpp.ast.expr.cpp;

import jcpp.model.cpp.ast.expr.*;
import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.name.*;
import jcpp.model.cpp.ast.expr.init.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPExpressionList extends ASTExpressionList{
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTImplicitName> implicitNames;

	public ASTCPPExpressionList(ICPPASTExpressionList expr) throws Exception{
		super(expr);
		implicitNames=new ArrayList<ASTImplicitName>();
		if (expr.getImplicitNames()!=null){
			for (IASTImplicitName n : expr.getImplicitNames()){
				implicitNames.add((ASTImplicitName)ASTNameFactory.create(n));
			}
		}
	}

	public ASTCPPExpressionList(){
	}

	public List<ASTImplicitName> getImplicitNames(){
		return implicitNames;
	}

	public void addImplicitName(ASTImplicitName n){
		implicitNames.add(n);
	}
}
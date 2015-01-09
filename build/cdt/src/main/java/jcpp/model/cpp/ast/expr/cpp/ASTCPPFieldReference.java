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
public class ASTCPPFieldReference extends ASTFieldReferenceExpression{
	@XmlElement
	private boolean bIsTemplate;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTImplicitName> implicitNames;

	public ASTCPPFieldReference(ICPPASTFieldReference expr) throws Exception{
		super(expr);
		bIsTemplate=expr.isTemplate();
		implicitNames=new ArrayList<ASTImplicitName>();
		if (expr.getImplicitNames()!=null){
			for (IASTImplicitName n : expr.getImplicitNames()){
				implicitNames.add((ASTImplicitName)ASTNameFactory.create(n));
			}
		}
	}

	public ASTCPPFieldReference(){
	}

	public boolean isTemplate(){
		return bIsTemplate;
	}

	public void setIsTemplate(boolean b){
		bIsTemplate=b;
	}

	public List<ASTImplicitName> getImplicitNames(){
		return implicitNames;
	}

	public void addImplicitName(ASTImplicitName n){
		implicitNames.add(n);
	}
}
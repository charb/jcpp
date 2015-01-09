package jcpp.model.cpp.ast.declaration.cpp;

import jcpp.model.cpp.ast.declaration.*;
import jcpp.model.cpp.ast.name.*;
import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.cpp.*;
import jcpp.model.cpp.ast.declarator.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import java.util.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPTemplateDeclaration extends ASTDeclaration{
	@XmlElement
	private ASTNodeWrapper<ASTDeclaration> declaration;
	@XmlElement
	private boolean bIsExported;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTCPPTemplateParameter> templateParameters;

	public ASTCPPTemplateDeclaration(ICPPASTTemplateDeclaration d) throws Exception{
		super(d);
		declaration=new ASTNodeWrapper<ASTDeclaration>();
		if (d.getDeclaration()!=null){
			declaration.set((ASTDeclaration)ASTDeclarationFactory.create(d.getDeclaration()));
		}

		templateParameters=new ArrayList<ASTCPPTemplateParameter>();
		if (d.getTemplateParameters()!=null){
			for (ICPPASTTemplateParameter p : d.getTemplateParameters()){
				templateParameters.add((ASTCPPTemplateParameter)ASTCPPTemplateParameterFactory.create(p));
			}
		}
		bIsExported=d.isExported();
	}

	public ASTCPPTemplateDeclaration(){
		declaration=new ASTNodeWrapper<ASTDeclaration>();
	}

	public ASTDeclaration getDeclaration(){
		return declaration.get();
	}

	public void setDeclaration(ASTDeclaration d){
		declaration.set(d);
	}

	public List<ASTCPPTemplateParameter> getTemplateParameters(){
		return templateParameters;
	}

	public void addTemplateParameter(ASTCPPTemplateParameter p){
		templateParameters.add(p);
	}

	public boolean isExported(){
		return bIsExported;
	}

	public void setIsExported(boolean b){
		bIsExported=b;
	}
}
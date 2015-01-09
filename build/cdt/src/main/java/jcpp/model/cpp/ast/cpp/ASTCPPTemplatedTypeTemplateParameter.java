package jcpp.model.cpp.ast.cpp;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.expr.*;
import jcpp.model.cpp.ast.name.*;
import jcpp.model.cpp.ast.attribute.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import java.util.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPTemplatedTypeTemplateParameter extends ASTCPPTemplateParameter{
	@XmlElement
	private ASTNodeWrapper<ASTExpression> defaultValue;
	@XmlElement
	private ASTNodeWrapper<ASTName> name;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTCPPTemplateParameter> templateParameters;

	public ASTCPPTemplatedTypeTemplateParameter(ICPPASTTemplatedTypeTemplateParameter p) throws Exception{
		super(p);

		defaultValue=new ASTNodeWrapper<ASTExpression>();
		if (p.getDefaultValue()!=null){
			defaultValue.set(ASTExpressionFactory.create(p.getDefaultValue()));
		}

		name=new ASTNodeWrapper<ASTName>();
		if (p.getName()!=null){
			name.set(ASTNameFactory.create(p.getName()));
		}
		
		templateParameters=new ArrayList<ASTCPPTemplateParameter>();
		if (p.getTemplateParameters()!=null){
			for (ICPPASTTemplateParameter p1 : p.getTemplateParameters()){
				templateParameters.add((ASTCPPTemplateParameter)ASTCPPTemplateParameterFactory.create(p1));
			}
		}
	}

	public ASTCPPTemplatedTypeTemplateParameter(){
		defaultValue=new ASTNodeWrapper<ASTExpression>();
		name=new ASTNodeWrapper<ASTName>();
	}

	public ASTExpression getDefaultValue(){
		return defaultValue.get();
	}

	public void setDefaultValue(ASTExpression e){
		defaultValue.set(e);
	}

	public ASTName getName(){
		return name.get();
	}

	public void setName(ASTName n){
		name.set(n);
	}

	public List<ASTCPPTemplateParameter> getTemplateParameters(){
		return templateParameters;
	}

	public void addTemplateParameter(ASTCPPTemplateParameter p){
		templateParameters.add(p);
	}
}
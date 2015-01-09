package jcpp.model.cpp.ast.name.cpp;

import jcpp.model.cpp.ast.name.*;
import jcpp.model.cpp.ast.declaration.specifier.*;
import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.location.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import java.util.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPTemplateId extends ASTCPPName{
	@XmlElement
	private ASTNodeWrapper<ASTName> templateName;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTNode> templateArguments;

	public ASTCPPTemplateId(ICPPASTTemplateId name) throws Exception{
		super(name);
		templateArguments=new ArrayList<ASTNode>();
		if (name.getTemplateArguments()!=null){
			for (IASTNode s : name.getTemplateArguments()){
				templateArguments.add((ASTNode)ASTNodeFactory.create(s));
			}
		}

		templateName=new ASTNodeWrapper<ASTName>();
		if (name.getTemplateName()!=null){
			templateName.set(ASTNameFactory.create(name.getTemplateName()));
		}
	}

	public ASTCPPTemplateId(){
		templateName=new ASTNodeWrapper<ASTName>();
	}

	public ASTName getTemplateName(){
		return templateName.get();
	}

	public void setTemplateName(ASTName t){
		templateName.set(t);
	}

	public List<ASTNode> getTemplateArguments(){
		return templateArguments;
	}

	public void addTemplateArgument(ASTNode n){
		templateArguments.add(n);
	}
}
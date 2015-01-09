package jcpp.model.cpp.ast.declaration.cpp;

import jcpp.model.cpp.ast.declaration.*;
import jcpp.model.cpp.ast.attribute.*;
import jcpp.model.cpp.ast.name.*;
import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.declarator.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import java.util.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPUsingDirective extends ASTDeclaration{
	@XmlElement
	private ASTNodeWrapper<ASTName> qualifiedName;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTAttribute> attributes;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTAttributeSpecifier> attributeSpecifiers;

	public ASTCPPUsingDirective(ICPPASTUsingDirective d) throws Exception{
		super(d);
		
		qualifiedName=new ASTNodeWrapper<ASTName>();
		if (d.getQualifiedName()!=null){
			qualifiedName.set(ASTNameFactory.create(d.getQualifiedName()));
		}

		attributes=new ArrayList<ASTAttribute>();
		if (d.getAttributes()!=null){
			for (IASTAttribute a : d.getAttributes()){
				attributes.add(ASTAttributeFactory.create(a));
			}
		}

		attributeSpecifiers=new ArrayList<ASTAttributeSpecifier>();
		if (d.getAttributeSpecifiers()!=null){
			for (IASTAttributeSpecifier a : d.getAttributeSpecifiers()){
				attributeSpecifiers.add(ASTAttributeSpecifierFactory.create(a));
			}
		}
	}

	public ASTCPPUsingDirective(){
		qualifiedName=new ASTNodeWrapper<ASTName>();
	}

	public ASTName getQualifiedName(){
		return qualifiedName.get();
	}

	public void setQualifiedName(ASTName n){
		qualifiedName.set(n);
	}

	public List<ASTAttribute> getAttributes(){
		return attributes;
	}

	public void addAttribute(ASTAttribute a){
		attributes.add(a);
	}

	public List<ASTAttributeSpecifier> getAttributeSpecifiers(){
		return attributeSpecifiers;
	}

	public void addAttributeSpecifier(ASTAttributeSpecifier a){
		attributeSpecifiers.add(a);
	}
}
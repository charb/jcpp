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
public class ASTCPPUsingDeclaration extends ASTDeclaration{
	@XmlElement
	private ASTNodeWrapper<ASTName> name;
	@XmlElement
	private boolean bIsTypeName; 
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTAttribute> attributes;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTAttributeSpecifier> attributeSpecifiers;

	public ASTCPPUsingDeclaration(ICPPASTUsingDeclaration d) throws Exception{
		super(d);
		name=new ASTNodeWrapper<ASTName>();
		if (d.getName()!=null){
			name.set(ASTNameFactory.create(d.getName()));
		}

		bIsTypeName=d.isTypename();

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

	public ASTCPPUsingDeclaration(){
		name=new ASTNodeWrapper<ASTName>();
	}

	public ASTName getName(){
		return name.get();
	}

	public void setName(ASTName n){
		name.set(n);
	}

	public boolean isTypename(){
		return bIsTypeName;
	}

	public void setTypename(boolean b){
		bIsTypeName=b;
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
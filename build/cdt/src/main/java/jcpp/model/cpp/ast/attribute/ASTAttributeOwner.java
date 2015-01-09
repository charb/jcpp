package jcpp.model.cpp.ast.attribute;

import jcpp.model.cpp.ast.*;
import org.eclipse.cdt.core.dom.ast.*;
import java.util.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTAttributeOwner extends ASTNode{
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTAttribute> attributes;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTAttributeSpecifier> attributeSpecifiers;

	public ASTAttributeOwner(IASTAttributeOwner decl) throws Exception{
		super(decl);
		attributes=new ArrayList<ASTAttribute>();
		if (decl.getAttributes()!=null){
			for (IASTAttribute a : decl.getAttributes()){
				attributes.add(ASTAttributeFactory.create(a));
			}
		}

		attributeSpecifiers=new ArrayList<ASTAttributeSpecifier>();
		if (decl.getAttributeSpecifiers()!=null){
			for (IASTAttributeSpecifier a : decl.getAttributeSpecifiers()){
				attributeSpecifiers.add(ASTAttributeSpecifierFactory.create(a));
			}
		}
	}

	public ASTAttributeOwner(){
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
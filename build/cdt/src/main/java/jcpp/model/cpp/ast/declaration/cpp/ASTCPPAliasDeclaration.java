package jcpp.model.cpp.ast.declaration.cpp;

import jcpp.model.cpp.ast.declaration.*;
import jcpp.model.cpp.ast.attribute.*;
import jcpp.model.cpp.ast.name.*;
import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.declarator.*;
import jcpp.model.cpp.ast.id.*;
import jcpp.model.cpp.ast.id.cpp.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import java.util.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPAliasDeclaration extends ASTDeclaration{
	@XmlElement
	private ASTNodeWrapper<ASTName> alias;
	@XmlElement
	private ASTNodeWrapper<ASTCPPTypeId> mappingTypeId;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTAttribute> attributes;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTAttributeSpecifier> attributeSpecifiers;

	public ASTCPPAliasDeclaration(ICPPASTAliasDeclaration d) throws Exception{
		super(d);
		alias=new ASTNodeWrapper<ASTName>();
		if (d.getAlias()!=null){
			alias.set(ASTNameFactory.create(d.getAlias()));
		}

		mappingTypeId=new ASTNodeWrapper<ASTCPPTypeId>();
		if (d.getMappingTypeId()!=null){
			mappingTypeId.set((ASTCPPTypeId)ASTTypeIdFactory.create(d.getMappingTypeId()));
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

	public ASTCPPAliasDeclaration(){
		alias=new ASTNodeWrapper<ASTName>();
		mappingTypeId=new ASTNodeWrapper<ASTCPPTypeId>();
	}

	public ASTName getAlias(){
		return alias.get();
	}

	public void setAlias(ASTName n){
		alias.set(n);
	}

	public ASTCPPTypeId getMappingTypeId(){
		return mappingTypeId.get();
	}

	public void setMappingTypeId(ASTCPPTypeId i){
		mappingTypeId.set(i);
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
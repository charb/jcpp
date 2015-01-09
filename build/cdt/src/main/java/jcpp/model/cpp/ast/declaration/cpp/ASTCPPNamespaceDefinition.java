package jcpp.model.cpp.ast.declaration.cpp;

import jcpp.model.cpp.ast.declaration.*;
import jcpp.model.cpp.ast.name.*;
import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.attribute.*;
import jcpp.model.cpp.ast.declarator.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import java.util.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPNamespaceDefinition extends ASTDeclaration{
	@XmlElement
	private ASTNodeWrapper<ASTName> name;
	@XmlElement
	private boolean inline;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTDeclaration> declarations;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTAttribute> attributes;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTAttributeSpecifier> attributeSpecifiers;

	public ASTCPPNamespaceDefinition(ICPPASTNamespaceDefinition d) throws Exception{
		super(d);

		declarations=new ArrayList<ASTDeclaration>();
		if (d.getDeclarations()!=null){
			for (IASTDeclaration de : d.getDeclarations()){
				declarations.add((ASTDeclaration)ASTDeclarationFactory.create(de));
			}
		}

		name=new ASTNodeWrapper<ASTName>();
		if (d.getName()!=null){
			name.set(ASTNameFactory.create(d.getName()));
		}
		inline=d.isInline();

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

	public ASTCPPNamespaceDefinition(){
		name=new ASTNodeWrapper<ASTName>();
	}

	public List<ASTDeclaration> getDeclarations(){
		return declarations;
	}

	public void addDeclaration(ASTDeclaration d){
		declarations.add(d);
	}

	public ASTName getName(){
		return name.get();
	}

	public void setName(ASTName n){
		name.set(n);
	}

	public boolean isInline(){
		return inline;
	}

	public void setInline(boolean b){
		inline=b;
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
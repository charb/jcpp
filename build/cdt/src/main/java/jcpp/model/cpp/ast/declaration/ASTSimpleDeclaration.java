package jcpp.model.cpp.ast.declaration;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.attribute.*;
import jcpp.model.cpp.ast.declarator.*;
import jcpp.model.cpp.ast.declaration.specifier.*;
import org.eclipse.cdt.core.dom.ast.*;
import java.util.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTSimpleDeclaration extends ASTDeclaration{
	@XmlElement
	private ASTNodeWrapper<ASTDeclSpecifier> declSpecifier;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTDeclarator> declarators;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTAttribute> attributes;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTAttributeSpecifier> attributeSpecifiers;

	public ASTSimpleDeclaration(IASTSimpleDeclaration d) throws Exception{
		super(d);
		declarators=new ArrayList<ASTDeclarator>();
		if (d.getDeclarators()!=null){
			for (IASTDeclarator de : d.getDeclarators()){
				declarators.add(ASTDeclaratorFactory.create(de));
			}
		}

		declSpecifier=new ASTNodeWrapper<ASTDeclSpecifier>();
		if (d.getDeclSpecifier()!=null){
			declSpecifier.set((ASTDeclSpecifier)ASTDeclSpecifierFactory.create(d.getDeclSpecifier()));
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

	public ASTSimpleDeclaration(){
		declSpecifier=new ASTNodeWrapper<ASTDeclSpecifier>();
	}

	public List<ASTDeclarator> getDeclarators(){
		return declarators;
	}

	public void addDeclarator(ASTDeclarator d){
		declarators.add(d);
	}

	public ASTDeclSpecifier getDeclSpecifier(){
		return declSpecifier.get();
	}

	public void setDeclSpecifier(ASTDeclSpecifier d){
		declSpecifier.set(d);
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
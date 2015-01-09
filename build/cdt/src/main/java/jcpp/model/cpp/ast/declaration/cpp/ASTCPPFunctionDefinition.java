package jcpp.model.cpp.ast.declaration.cpp;

import jcpp.model.cpp.ast.declaration.*;
import jcpp.model.cpp.ast.attribute.*;
import jcpp.model.cpp.ast.expr.init.*;
import jcpp.model.cpp.ast.expr.init.cpp.*;
import jcpp.model.cpp.ast.name.*;
import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.declarator.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import java.util.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPFunctionDefinition extends ASTFunctionDefinition{
	@XmlElement
	private boolean bIsDeleted;
	@XmlElement
	private boolean bIsDefaulted;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTCPPConstructorChainInitializer> memberInitializers;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTAttribute> attributes;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTAttributeSpecifier> attributeSpecifiers;

	public ASTCPPFunctionDefinition(ICPPASTFunctionDefinition d) throws Exception{
		super(d);
		bIsDeleted=d.isDeleted();
		bIsDefaulted=d.isDefaulted();
		memberInitializers=new ArrayList<ASTCPPConstructorChainInitializer>();
		if (d.getMemberInitializers()!=null){
			for (ICPPASTConstructorChainInitializer ci : d.getMemberInitializers()){
				memberInitializers.add(new ASTCPPConstructorChainInitializer(ci));
			}
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

	public ASTCPPFunctionDefinition(){
	}

	public boolean isDeleted(){
		return bIsDeleted;
	}

	public void setIsDeleted(boolean b){
		bIsDefaulted=b;
	}

	public boolean isDefaulted(){
		return bIsDefaulted;
	}

	public void setIsDefaulted(boolean b){
		bIsDefaulted=b;
	}

	public List<ASTCPPConstructorChainInitializer> getMemberInitializers(){
		return memberInitializers;
	}

	public void addMemberInitializer(ASTCPPConstructorChainInitializer c){
		memberInitializers.add(c);
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
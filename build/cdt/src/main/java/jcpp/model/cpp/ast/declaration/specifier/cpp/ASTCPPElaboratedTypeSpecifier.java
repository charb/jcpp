package jcpp.model.cpp.ast.declaration.specifier.cpp;

import jcpp.model.cpp.ast.declaration.specifier.*;
import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.attribute.*;
import jcpp.model.cpp.ast.declaration.*;
import jcpp.model.cpp.ast.name.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import java.util.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPElaboratedTypeSpecifier extends ASTElaboratedTypeSpecifier{
	@XmlElement
	private boolean bIsConstexpr;
	@XmlElement
	private boolean bIsExplicit;
	@XmlElement
	private boolean bIsFriend;
	@XmlElement
	private boolean bIsThreadLocal;
	@XmlElement
	private boolean bIsVirtual;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTAttribute> attributes;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTAttributeSpecifier> attributeSpecifiers;

	public ASTCPPElaboratedTypeSpecifier(ICPPASTElaboratedTypeSpecifier s) throws Exception{
		super(s);
		bIsConstexpr=s.isConstexpr();
		bIsExplicit=s.isExplicit();
		bIsFriend=s.isFriend();
		bIsThreadLocal=s.isThreadLocal();
		bIsVirtual=s.isVirtual();

		attributes=new ArrayList<ASTAttribute>();
		if (s.getAttributes()!=null){
			for (IASTAttribute a : s.getAttributes()){
				attributes.add(ASTAttributeFactory.create(a));
			}
		}

		attributeSpecifiers=new ArrayList<ASTAttributeSpecifier>();
		if (s.getAttributeSpecifiers()!=null){
			for (IASTAttributeSpecifier a : s.getAttributeSpecifiers()){
				attributeSpecifiers.add(ASTAttributeSpecifierFactory.create(a));
			}
		}
	}

	public ASTCPPElaboratedTypeSpecifier(){
	}

	public boolean isConstexpr(){
		return bIsConstexpr;
	}

	public void setIsConstexpr(boolean b){
		bIsConstexpr=b;
	}

	public boolean isExplicit(){
		return bIsExplicit;
	}

	public void setIsExplicit(boolean b){
		bIsExplicit=b;
	}

	public boolean isFriend(){
		return bIsFriend;
	}

	public void setIsFriend(boolean b){
		bIsFriend=b;
	}

	public boolean isThreadLocal(){
		return bIsThreadLocal;
	}

	public void setIsThreadLocal(boolean b){
		bIsThreadLocal=b;
	}

	public boolean isVirtual(){
		return bIsVirtual;
	}

	public void setIsVirtual(boolean b){
		bIsVirtual=b;
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
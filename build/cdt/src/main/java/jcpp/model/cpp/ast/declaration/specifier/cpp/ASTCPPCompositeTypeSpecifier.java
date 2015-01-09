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
public class ASTCPPCompositeTypeSpecifier extends ASTCompositeTypeSpecifier{
	@XmlElement
	private boolean bFinal;
	@XmlElement
	private ASTNodeWrapper<ASTCPPClassVirtSpecifier> virtSpecifier;
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
	private List<ASTCPPBaseSpecifier> baseSpecifiers;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTAttribute> attributes;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTAttributeSpecifier> attributeSpecifiers;

	public ASTCPPCompositeTypeSpecifier(ICPPASTCompositeTypeSpecifier s) throws Exception{
		super(s);

		bFinal=s.isFinal();

		baseSpecifiers=new ArrayList<ASTCPPBaseSpecifier>();
		if (s.getBaseSpecifiers()!=null){
			for (ICPPASTCompositeTypeSpecifier.ICPPASTBaseSpecifier d : s.getBaseSpecifiers()){
				baseSpecifiers.add(new ASTCPPBaseSpecifier(d));
			}
		}

		virtSpecifier=new ASTNodeWrapper<ASTCPPClassVirtSpecifier>();
		if (s.getVirtSpecifier()!=null){
			virtSpecifier.set(new ASTCPPClassVirtSpecifier(s.getVirtSpecifier()));
		}

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

	public ASTCPPCompositeTypeSpecifier(){
		virtSpecifier=new ASTNodeWrapper<ASTCPPClassVirtSpecifier>();
	}

	public boolean isFinal(){
		return bFinal;
	}

	public void setIsFinal(boolean k){
		bFinal=k;
	}

	public ASTCPPClassVirtSpecifier getVirtSpecifier(){
		return virtSpecifier.get();
	}

	public void setVirtSpecifier(ASTCPPClassVirtSpecifier v){
		virtSpecifier.set(v);
	}

	public List<ASTCPPBaseSpecifier> getBaseSpecifiers(){
		return baseSpecifiers;
	}

	public void addBaseSpecifier(ASTCPPBaseSpecifier d){
		baseSpecifiers.add(d);
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
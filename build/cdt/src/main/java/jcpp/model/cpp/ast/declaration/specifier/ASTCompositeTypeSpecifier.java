package jcpp.model.cpp.ast.declaration.specifier;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.declaration.*;
import jcpp.model.cpp.ast.name.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import java.util.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCompositeTypeSpecifier extends ASTDeclSpecifier{
	@XmlElement
	private String key;
	@XmlElement
	private ASTNodeWrapper<ASTName> name;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTDeclaration> members;

	public ASTCompositeTypeSpecifier(IASTCompositeTypeSpecifier s) throws Exception{
		super(s);
		key=getKey(s.getKey());
		members=new ArrayList<ASTDeclaration>();
		if (s.getMembers()!=null){
			for (IASTDeclaration d : s.getMembers()){
				members.add((ASTDeclaration)ASTDeclarationFactory.create(d));
			}
		}
		name=new ASTNodeWrapper<ASTName>();
		if (s.getName()!=null){
			name.set(ASTNameFactory.create(s.getName()));
		}
	}

	public ASTCompositeTypeSpecifier(){
		name=new ASTNodeWrapper<ASTName>();
	}

	public static String getKey(int k){
		if (k==IASTCompositeTypeSpecifier.k_struct){
			return "k_struct";
		}else if (k==IASTCompositeTypeSpecifier.k_union){
			return "k_union";
		}else if (k==ICPPASTCompositeTypeSpecifier.k_class){
			return "k_class";
		}else{
			return "unknown";
		}
	}

	public String getKey(){
		return key;
	}

	public void setKey(String k){
		key=k;
	}

	public List<ASTDeclaration> getMembers(){
		return members;
	}

	public void addMember(ASTDeclaration d){
		members.add(d);
	}

	public ASTName getName(){
		return name.get();
	}

	public void setName(ASTName n){
		name.set(n);
	}
}
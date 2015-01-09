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
public class ASTElaboratedTypeSpecifier extends ASTDeclSpecifier{
	@XmlElement
	private String kind;
	@XmlElement
	private ASTNodeWrapper<ASTName> name;

	public ASTElaboratedTypeSpecifier(IASTElaboratedTypeSpecifier s) throws Exception{
		super(s);
		kind=getKind(s.getKind());
		name=new ASTNodeWrapper<ASTName>();
		if (s.getName()!=null){
			name.set(ASTNameFactory.create(s.getName()));
		}
	}

	public ASTElaboratedTypeSpecifier(){
		name=new ASTNodeWrapper<ASTName>();
	}

	public static String getKind(int i){
		if (i==IASTElaboratedTypeSpecifier.k_enum){
			return "k_enum";
		}else if (i==IASTElaboratedTypeSpecifier.k_struct){
			return "k_struct";
		}else if (i==IASTElaboratedTypeSpecifier.k_union){
			return "k_union";
		}else if (i==ICPPASTElaboratedTypeSpecifier.k_class){
			return "k_class";
		}else{
			return "unknown";
		}
	}

	public String getKind(){
		return kind;
	}

	public void setKind(String k){
		kind=k;
	}

	public ASTName getName(){
		return name.get();
	}

	public void setName(ASTName n){
		name.set(n);
	}
}
package jcpp.model.cpp.ast.declaration.specifier.cpp;

import jcpp.model.cpp.ast.declaration.specifier.*;
import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.name.*;
import jcpp.model.cpp.ast.attribute.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import java.util.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPBaseSpecifier extends ASTNode{
	@XmlElement
	private boolean bIsVirtual;
	@XmlElement
	private String visibility;
	@XmlElement
	private ASTNodeWrapper<ASTName> name;
	@XmlElement
	private boolean bIsPackExpansion;

	public ASTCPPBaseSpecifier(ICPPASTCompositeTypeSpecifier.ICPPASTBaseSpecifier s) throws Exception{
		super(s);
		bIsVirtual=s.isVirtual();
		visibility=getVisibility(s.getVisibility());
		name=new ASTNodeWrapper<ASTName>();
		if (s.getName()!=null){
			name.set(ASTNameFactory.create(s.getName()));
		}
		bIsPackExpansion=s.isPackExpansion();
	}

	public ASTCPPBaseSpecifier(){
		name=new ASTNodeWrapper<ASTName>();
	}
	
	public boolean isVirtual(){
		return bIsVirtual;
	}

	public void setIsVirtual(boolean b){
		bIsVirtual=b;
	}

	public static String getVisibility(int i){
		if (i==ICPPASTCompositeTypeSpecifier.ICPPASTBaseSpecifier.v_private){
			return "v_private";
		}else if (i==ICPPASTCompositeTypeSpecifier.ICPPASTBaseSpecifier.v_protected){
			return "v_protected";
		}else if (i==ICPPASTCompositeTypeSpecifier.ICPPASTBaseSpecifier.v_public){
			return "v_public";
		}else{
			return "unkown";
		}
	}

	public String getVisibility(){
		return visibility;
	}

	public void setVisibility(String b){
		visibility=b;
	}

	public ASTName getName(){
		return name.get();
	}

	public void setName(ASTName b){
		name.set(b);
	}

	public boolean isPackExpansion(){
		return bIsPackExpansion;
	}

	public void setIsPackExpansion(boolean b){
		bIsPackExpansion=b;
	}
}
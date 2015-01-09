package jcpp.model.cpp.ast.declaration.cpp;

import jcpp.model.cpp.ast.declaration.*;
import jcpp.model.cpp.ast.name.*;
import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.declarator.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import java.util.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPExplicitTemplateInstantiation extends ASTDeclaration{
	@XmlElement
	private ASTNodeWrapper<ASTDeclaration> declaration;
	@XmlElement
	private String modifier;

	public ASTCPPExplicitTemplateInstantiation(ICPPASTExplicitTemplateInstantiation d) throws Exception{
		super(d);
		declaration=new ASTNodeWrapper<ASTDeclaration>();
		if (d.getDeclaration()!=null){
			declaration.set((ASTDeclaration)ASTDeclarationFactory.create(d.getDeclaration()));
		}
		modifier=getModifier(d.getModifier());
	}

	public ASTCPPExplicitTemplateInstantiation(){
		declaration=new ASTNodeWrapper<ASTDeclaration>();
	}

	public ASTDeclaration getDeclaration(){
		return declaration.get();
	}

	public void setDeclaration(ASTDeclaration d){
		declaration.set(d);
	}

	public static String getModifier(int i){
		if (i==ICPPASTExplicitTemplateInstantiation.EXTERN){
			return "EXTERN";
		}else if (i==ICPPASTExplicitTemplateInstantiation.INLINE){
			return "INLINE";
		}else if (i==ICPPASTExplicitTemplateInstantiation.STATIC){
			return "STATIC";
		}else{
			return "unknown";
		}
	}

	public String getModifier(){
		return modifier;
	}

	public void setModifier(String m){
		modifier=m;
	}
}
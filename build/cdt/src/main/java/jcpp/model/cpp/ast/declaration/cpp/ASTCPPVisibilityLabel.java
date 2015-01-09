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
public class ASTCPPVisibilityLabel extends ASTDeclaration{
	@XmlElement
	private String visibility;

	public ASTCPPVisibilityLabel(ICPPASTVisibilityLabel d) throws Exception{
		super(d);
		visibility=getVisibility(d.getVisibility());
	}

	public ASTCPPVisibilityLabel(){
	}

	public static String getVisibility(int i){
		if (i==ICPPASTVisibilityLabel.v_private){
			return "v_private";
		}else if (i==ICPPASTVisibilityLabel.v_protected){
			return "v_protected";
		}else if (i==ICPPASTVisibilityLabel.v_public){
			return "v_public";
		}else {
			return "unknown";
		}
	}

	public String getVisibility(){
		return visibility;
	}

	public void setVisibility(String n){
		visibility=n;
	}
}
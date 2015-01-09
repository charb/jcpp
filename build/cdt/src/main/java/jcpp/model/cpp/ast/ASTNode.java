package jcpp.model.cpp.ast;

import org.eclipse.cdt.core.dom.ast.*;
import jcpp.model.cpp.ast.location.*;
import java.util.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTNode{
	@XmlTransient
	private String containingFilename;

	public ASTNode(IASTNode node) throws Exception{
		containingFilename=node.getContainingFilename();
	}

	public ASTNode(){
	}

	public String getContainingFilename(){
		return containingFilename;
	}

	public void setContainingFilename(String s){
		containingFilename=s;
	}
}
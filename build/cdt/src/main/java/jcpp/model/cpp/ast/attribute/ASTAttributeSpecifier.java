package jcpp.model.cpp.ast.attribute;

import jcpp.model.cpp.ast.*;
import org.eclipse.cdt.core.dom.ast.*;
import java.util.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTAttributeSpecifier extends ASTNode{
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTAttribute> attributes;

	public ASTAttributeSpecifier(IASTAttributeSpecifier decl) throws Exception{
		super(decl);
		attributes=new ArrayList<ASTAttribute>();
		if (decl.getAttributes()!=null){
			for (IASTAttribute a : decl.getAttributes()){
				attributes.add(ASTAttributeFactory.create(a));
			}
		}
	}

	public ASTAttributeSpecifier(){
	}

	public List<ASTAttribute> getAttributes(){
		return attributes;
	}

	public void addAttribute(ASTAttribute a){
		attributes.add(a);
	}
}
package jcpp.model.cpp.ast.declarator;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.name.*;
import jcpp.model.cpp.ast.ptr.*;
import jcpp.model.cpp.ast.expr.init.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTArrayDeclarator extends ASTDeclarator{
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTArrayModifier> arrayModifiers;

	public ASTArrayDeclarator(IASTArrayDeclarator decl) throws Exception{
		super(decl);
		arrayModifiers=new ArrayList<ASTArrayModifier>();
		if (decl.getArrayModifiers()!=null){
			for (IASTArrayModifier m : decl.getArrayModifiers()){
				arrayModifiers.add(ASTArrayModifierFactory.create(m));
			}
		}
	}

	public ASTArrayDeclarator(){
	}

	public List<ASTArrayModifier> getArrayModifiers(){
		return arrayModifiers;
	}

	public void addArrayModifier(ASTArrayModifier a){
		arrayModifiers.add(a);
	}
}
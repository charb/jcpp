package jcpp.model.cpp.ast.declaration.specifier;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.declaration.*;
import jcpp.model.cpp.ast.name.*;
import org.eclipse.cdt.core.dom.ast.*;
import java.util.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTNamedTypeSpecifier extends ASTDeclSpecifier{
	@XmlElement
	private ASTNodeWrapper<ASTName> name;

	public ASTNamedTypeSpecifier(IASTNamedTypeSpecifier s) throws Exception{
		super(s);
		name=new ASTNodeWrapper<ASTName>();
		if (s.getName()!=null){
			name.set(ASTNameFactory.create(s.getName()));
		}
	}

	public ASTNamedTypeSpecifier(){
		name=new ASTNodeWrapper<ASTName>();
	}

	public ASTName getName(){
		return name.get();
	}

	public void setName(ASTName n){
		name.set(n);
	}
}
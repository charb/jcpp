package jcpp.model.cpp.ast.c;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.name.*;
import jcpp.model.cpp.ast.attribute.*;
import jcpp.model.cpp.ast.expr.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.c.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCFieldDesignator extends ASTCDesignator{
	@XmlElement
	private ASTNodeWrapper<ASTName> name;

	public ASTCFieldDesignator(ICASTFieldDesignator p) throws Exception{
		super(p);
		name=new ASTNodeWrapper<ASTName>();
		if (p.getName()!=null){
			name.set(ASTNameFactory.create(p.getName()));
		}
	}

	public ASTCFieldDesignator(){
		name=new ASTNodeWrapper<ASTName>();
	}

	public ASTName getName(){
		return name.get();
	}

	public void setName(ASTName e){
		name.set(e);
	}
}
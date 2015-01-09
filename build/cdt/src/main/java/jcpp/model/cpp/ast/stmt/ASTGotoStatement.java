package jcpp.model.cpp.ast.stmt;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.expr.*;
import jcpp.model.cpp.ast.name.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTGotoStatement extends ASTStatement{
	@XmlElement
	private ASTNodeWrapper<ASTName> name;

	public ASTGotoStatement(IASTGotoStatement s) throws Exception{
		super(s);
		name=new ASTNodeWrapper<ASTName>();
		if (s.getName()!=null){
			name.set(ASTNameFactory.create(s.getName()));
		}
	}

	public ASTGotoStatement(){
		name=new ASTNodeWrapper<ASTName>();
	}

	public ASTName getName(){
		return name.get();
	}

	public void setName(ASTName s){
		name.set(s);
	}
}
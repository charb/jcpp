package jcpp.model.cpp.ast.expr.init;

import jcpp.model.cpp.ast.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import java.util.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTEqualsInitializer extends ASTInitializer{
	@XmlElement
	private ASTNodeWrapper<ASTInitializerClause> initializerClause;

	public ASTEqualsInitializer(IASTEqualsInitializer init) throws Exception{
		super(init);
		initializerClause=new ASTNodeWrapper<ASTInitializerClause>();
		if (init.getInitializerClause()!=null){
			initializerClause.set(ASTInitializerClauseFactory.create(init.getInitializerClause()));
		}
	}

	public ASTEqualsInitializer(){
		initializerClause=new ASTNodeWrapper<ASTInitializerClause>();
	}

	public ASTInitializerClause getInitializerClause(){
		return initializerClause.get();
	}

	public void setInitializerClause(ASTInitializerClause c){
		initializerClause.set(c);
	}
}
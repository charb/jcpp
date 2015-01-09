package jcpp.model.cpp.ast.expr.init.c;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.expr.init.*;
import jcpp.model.cpp.ast.c.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import org.eclipse.cdt.core.dom.ast.c.*;
import java.util.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCDesignatedInitializer extends ASTInitializer{
	@XmlElement
	private ASTNodeWrapper<ASTInitializerClause> operand;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTCDesignator> designators;	

	public ASTCDesignatedInitializer(ICASTDesignatedInitializer init) throws Exception{
		super(init);
		designators=new ArrayList<ASTCDesignator>();
		if (init.getDesignators()!=null){
			for (ICASTDesignator d : init.getDesignators()){
				designators.add(ASTCDesignatorFactory.create(d));
			}
		}

		operand=new ASTNodeWrapper<ASTInitializerClause>();
		if (init.getOperand()!=null){
			operand.set(ASTInitializerClauseFactory.create(init.getOperand()));
		}
	}

	public ASTCDesignatedInitializer(){
		operand=new ASTNodeWrapper<ASTInitializerClause>();
	}

	public List<ASTCDesignator> getDesignators(){
		return designators;
	}

	public void addDesignator(ASTCDesignator d){
		designators.add(d);
	}

	public ASTInitializerClause getOperand(){
		return operand.get();
	}

	public void setOperand(ASTInitializerClause c){
		operand.set(c);
	}
}
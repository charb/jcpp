package jcpp.model.cpp.ast.declarator;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.attribute.*;
import jcpp.model.cpp.ast.name.*;
import jcpp.model.cpp.ast.ptr.*;
import jcpp.model.cpp.ast.expr.init.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
//TODO check ASTNameOwner+ASTAttributeOwner
public class ASTDeclarator extends ASTAttributeOwner{
	@XmlElement
	private ASTNodeWrapper<ASTInitializer> initializer;
	@XmlElement
	private ASTNodeWrapper<ASTName> name;
	@XmlElement
	private ASTNodeWrapper<ASTDeclarator> nestedDeclarator;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTPointerOperator> pointerOperators;

	public ASTDeclarator(IASTDeclarator decl) throws Exception{
		super(decl);

		initializer=new ASTNodeWrapper<ASTInitializer>();
		if (decl.getInitializer()!=null){
			initializer.set(ASTInitializerFactory.create(decl.getInitializer()));
		}

		name=new ASTNodeWrapper<ASTName>();
		if (decl.getName()!=null){
			name.set(ASTNameFactory.create(decl.getName()));
		}

		nestedDeclarator=new ASTNodeWrapper<ASTDeclarator>();
		if (decl.getNestedDeclarator()!=null){
			nestedDeclarator.set(ASTDeclaratorFactory.create(decl.getNestedDeclarator()));
		}

		pointerOperators=new ArrayList<ASTPointerOperator>();
		if (decl.getPointerOperators()!=null){
			for (IASTPointerOperator p : decl.getPointerOperators()){
				pointerOperators.add(ASTPointerOperatorFactory.create(p));
			}
		}
	}

	public ASTDeclarator(){
		initializer=new ASTNodeWrapper<ASTInitializer>();
		name=new ASTNodeWrapper<ASTName>();
		nestedDeclarator=new ASTNodeWrapper<ASTDeclarator>();
	}

	public ASTInitializer getInitializer(){
		return initializer.get();
	}

	public void setInitializer(ASTInitializer i){
		initializer.set(i);
	}

	public ASTName getName(){
		return name.get();
	}

	public void setName(ASTName i){
		name.set(i);
	}

	public ASTDeclarator getNestedDeclarator(){
		return nestedDeclarator.get();
	}

	public void setNestedDeclarator(ASTDeclarator i){
		nestedDeclarator.set(i);
	}

	public List<ASTPointerOperator> getPointerOperators(){
		return pointerOperators;
	}

	public void addPointerOperator(ASTPointerOperator o){
		pointerOperators.add(o);
	}
}
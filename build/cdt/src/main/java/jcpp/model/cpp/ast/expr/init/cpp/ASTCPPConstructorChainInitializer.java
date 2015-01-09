package jcpp.model.cpp.ast.expr.init.cpp;

import jcpp.model.cpp.ast.expr.init.*;
import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.name.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import java.util.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPConstructorChainInitializer extends ASTInitializer{
	@XmlElement
	private ASTNodeWrapper<ASTName> memberInitializerId;
	@XmlElement
	private ASTNodeWrapper<ASTInitializer> initializer;
	@XmlElement
	private boolean bIsPackExpansion;

	public ASTCPPConstructorChainInitializer(ICPPASTConstructorChainInitializer init) throws Exception{
		super(init);
		memberInitializerId=new ASTNodeWrapper<ASTName>();
		if (init.getMemberInitializerId()!=null){
			memberInitializerId.set(ASTNameFactory.create(init.getMemberInitializerId()));
		}

		initializer=new ASTNodeWrapper<ASTInitializer>();
		if (init.getInitializer()!=null){
			initializer.set(ASTInitializerFactory.create(init.getInitializer()));
		}

		bIsPackExpansion=init.isPackExpansion();
	}

	public ASTCPPConstructorChainInitializer(){
		memberInitializerId=new ASTNodeWrapper<ASTName>();
		initializer=new ASTNodeWrapper<ASTInitializer>();
	}

	public ASTName getMemberInitializerId(){
		return memberInitializerId.get();
	}

	public void setMemberInitializerId(ASTName n){
		memberInitializerId.set(n);
	}

	public ASTInitializer getInitializer(){
		return initializer.get();
	}

	public void setInitializer(ASTInitializer i){
		initializer.set(i);
	}

	public boolean isPackExpansion(){
		return bIsPackExpansion;
	}

	public void setIsPackExpansion(boolean b){
		bIsPackExpansion=b;
	}
}
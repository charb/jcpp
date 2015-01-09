package jcpp.model.cpp.ast.expr.cpp;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.expr.init.*;
import jcpp.model.cpp.ast.expr.*;
import jcpp.model.cpp.ast.declaration.specifier.*;
import jcpp.model.cpp.ast.declaration.specifier.cpp.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPSimpleTypeConstructorExpression extends ASTCPPExpression{
	@XmlElement
	private ASTNodeWrapper<ASTCPPDeclSpecifier> declSpecifier;
	@XmlElement
	private ASTNodeWrapper<ASTInitializer> initializer;

	public ASTCPPSimpleTypeConstructorExpression(ICPPASTSimpleTypeConstructorExpression e) throws Exception{
		super(e);
		declSpecifier=new ASTNodeWrapper<ASTCPPDeclSpecifier>();
		if (e.getDeclSpecifier()!=null){
			declSpecifier.set((ASTCPPDeclSpecifier)ASTDeclSpecifierFactory.create(e.getDeclSpecifier()));
		}

		initializer=new ASTNodeWrapper<ASTInitializer>();
		if (e.getInitializer()!=null){
			initializer.set(ASTInitializerFactory.create(e.getInitializer()));
		}
	}

	public ASTCPPSimpleTypeConstructorExpression(){
		declSpecifier=new ASTNodeWrapper<ASTCPPDeclSpecifier>();
		initializer=new ASTNodeWrapper<ASTInitializer>();
	}

	public ASTCPPDeclSpecifier getDeclSpecifier(){
		return declSpecifier.get();
	}

	public void setDeclSpecifier(ASTCPPDeclSpecifier s){
		declSpecifier.set(s);
	}

	public ASTInitializer getInitializer(){
		return initializer.get();
	}

	public void setInitializer(ASTInitializer i){
		initializer.set(i);
	}
}
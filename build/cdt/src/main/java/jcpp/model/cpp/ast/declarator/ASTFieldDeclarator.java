package jcpp.model.cpp.ast.declarator;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.name.*;
import jcpp.model.cpp.ast.ptr.*;
import jcpp.model.cpp.ast.expr.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTFieldDeclarator extends ASTDeclarator{
	@XmlElement
	private ASTNodeWrapper<ASTExpression> bitFieldSize;

	public ASTFieldDeclarator(IASTFieldDeclarator decl) throws Exception{
		super(decl);
		bitFieldSize=new ASTNodeWrapper<ASTExpression>();
		if (decl.getBitFieldSize()!=null){
			bitFieldSize.set(ASTExpressionFactory.create(decl.getBitFieldSize()));
		}
	}

	public ASTFieldDeclarator(){
		bitFieldSize=new ASTNodeWrapper<ASTExpression>();
	}

	public ASTExpression getBitFieldSize(){
		return bitFieldSize.get();
	}

	public void setBitFieldSize(ASTExpression a){
		bitFieldSize.set(a);
	}
}
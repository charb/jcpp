package jcpp.model.cpp.ast.expr;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.id.*;
import jcpp.model.cpp.ast.expr.init.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTTypeIdInitializerExpression extends ASTExpression{
	@XmlElement
	private ASTNodeWrapper<ASTInitializer> initializer;
	@XmlElement
	private ASTNodeWrapper<ASTTypeId> typeId;

	public ASTTypeIdInitializerExpression(IASTTypeIdInitializerExpression expr) throws Exception{
		super(expr);
		typeId=new ASTNodeWrapper<ASTTypeId>();
		if (expr.getTypeId()!=null){
			typeId.set(ASTTypeIdFactory.create(expr.getTypeId()));
		}

		initializer=new ASTNodeWrapper<ASTInitializer>();
		if (expr.getInitializer()!=null){
			initializer.set(ASTInitializerFactory.create(expr.getInitializer()));
		}
	}

	public ASTTypeIdInitializerExpression(){
		typeId=new ASTNodeWrapper<ASTTypeId>();
		initializer=new ASTNodeWrapper<ASTInitializer>();
	}

	public ASTTypeId getTypeId(){
		return typeId.get();
	}

	public void setTypeId(ASTTypeId b){
		typeId.set(b);
	}

	public ASTInitializer getInitializer(){
		return initializer.get();
	}

	public void setInitializer(ASTInitializer b){
		initializer.set(b);
	}
}
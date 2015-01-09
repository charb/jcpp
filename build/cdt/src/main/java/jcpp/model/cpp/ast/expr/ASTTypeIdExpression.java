package jcpp.model.cpp.ast.expr;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.id.*;
import jcpp.model.cpp.ast.expr.init.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTTypeIdExpression extends ASTExpression{
	@XmlElement
	private ASTNodeWrapper<ASTTypeId> typeId;
	@XmlElement
	private String operator;

	public ASTTypeIdExpression(IASTTypeIdExpression expr) throws Exception{
		super(expr);
		typeId=new ASTNodeWrapper<ASTTypeId>();
		if (expr.getTypeId()!=null){
			typeId.set(ASTTypeIdFactory.create(expr.getTypeId()));
		}
		operator=getOperator(expr.getOperator());
	}

	public ASTTypeIdExpression(){
		typeId=new ASTNodeWrapper<ASTTypeId>();
	}

	public ASTTypeId getTypeId(){
		return typeId.get();
	}

	public void setTypeId(ASTTypeId b){
		typeId.set(b);
	}

	public static String getOperator(int i){
		if (i==IASTTypeIdExpression.op_alignof){
			return "op_alignof";
		}else if (i==IASTTypeIdExpression.op_has_nothrow_assign){
			return "op_has_nothrow_assign";
		}else if (i==IASTTypeIdExpression.op_has_nothrow_constructor){
			return "op_has_nothrow_constructor";
		}else if (i==IASTTypeIdExpression.op_has_nothrow_copy){
			return "op_has_nothrow_copy";
		}else if (i==IASTTypeIdExpression.op_has_trivial_assign){
			return "op_has_trivial_assign";
		}else if (i==IASTTypeIdExpression.op_has_trivial_constructor){
			return "op_has_trivial_constructor";
		}else if (i==IASTTypeIdExpression.op_has_trivial_copy){
			return "op_has_trivial_copy";
		}else if (i==IASTTypeIdExpression.op_has_trivial_destructor){
			return "op_has_trivial_destructor";
		}else if (i==IASTTypeIdExpression.op_has_virtual_destructor){
			return "op_has_virtual_destructor";
		}else if (i==IASTTypeIdExpression.op_is_abstract){
			return "op_is_abstract";
		}else if (i==IASTTypeIdExpression.op_is_class){
			return "op_is_class";
		}else if (i==IASTTypeIdExpression.op_is_empty){
			return "op_is_empty";
		}else if (i==IASTTypeIdExpression.op_is_enum){
			return "op_is_enum";
		}else if (i==IASTTypeIdExpression.op_is_final){
			return "op_is_final";
		}else if (i==IASTTypeIdExpression.op_is_literal_type){
			return "op_is_literal_type";
		}else if (i==IASTTypeIdExpression.op_is_pod){
			return "op_is_pod";
		}else if (i==IASTTypeIdExpression.op_is_polymorphic){
			return "op_is_polymorphic";
		}else if (i==IASTTypeIdExpression.op_is_standard_layout){
			return "op_is_standard_layout";
		}else if (i==IASTTypeIdExpression.op_is_trivial){
			return "op_is_trivial";
		}else if (i==IASTTypeIdExpression.op_is_union){
			return "op_is_union";
		}else if (i==IASTTypeIdExpression.op_sizeof){
			return "op_sizeof";
		}else if (i==IASTTypeIdExpression.op_sizeofParameterPack){
			return "op_sizeofParameterPack";
		}else if (i==IASTTypeIdExpression.op_typeid){
			return "op_typeid";
		}else if (i==IASTTypeIdExpression.op_typeof){
			return "op_typeof";
		}else{
			return "unknown";
		}
	}

	public String getOperator(){
		return operator;
	}

	public void setOperator(String b){
		operator=b;
	}
}
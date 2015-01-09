package jcpp.model.cpp.ast.expr;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.expr.init.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTLiteralExpression extends ASTExpression{
	@XmlElement
	private String kind;
	@XmlElement
	private String value;

	public ASTLiteralExpression(IASTLiteralExpression expr) throws Exception{
		super(expr);
		kind=getKind(expr.getKind());
		value=new String(expr.getValue());
	}

	public ASTLiteralExpression(){
	}

	public static String getKind(int i){
		if (i==IASTLiteralExpression.lk_char_constant){
			return "lk_char_constant";
		}else if (i==IASTLiteralExpression.lk_false){
			return "lk_false";
		}else if (i==IASTLiteralExpression.lk_float_constant){
			return "lk_float_constant";
		}else if (i==IASTLiteralExpression.lk_integer_constant){
			return "lk_integer_constant";
		}else if (i==IASTLiteralExpression.lk_nullptr){
			return "lk_nullptr";
		}else if (i==IASTLiteralExpression.lk_string_literal){
			return "lk_string_literal";
		}else if (i==IASTLiteralExpression.lk_this){
			return "lk_this";
		}else if (i==IASTLiteralExpression.lk_true){
			return "lk_true";
		}else{
			return "unknown";
		}
	}

	public String getKind(){
		return kind;
	}

	public void setKind(String b){
		kind=b;
	}

	public String getValue(){
		return value;
	}

	public void setValue(String b){
		value=b;
	}
}
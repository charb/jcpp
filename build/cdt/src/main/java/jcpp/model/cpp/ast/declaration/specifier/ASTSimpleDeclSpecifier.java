package jcpp.model.cpp.ast.declaration.specifier;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.declaration.*;
import jcpp.model.cpp.ast.name.*;
import jcpp.model.cpp.ast.expr.*;
import org.eclipse.cdt.core.dom.ast.*;
import java.util.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTSimpleDeclSpecifier extends ASTDeclSpecifier{
	@XmlElement
	private ASTNodeWrapper<ASTExpression> declTypeExpression;
	@XmlElement
	private String type;
	@XmlElement
	private boolean bIsComplex;
	@XmlElement
	private boolean bIsImaginary;
	@XmlElement
	private boolean bIsLong;
	@XmlElement
	private boolean bIsLongLong;
	@XmlElement
	private boolean bIsShort;
	@XmlElement
	private boolean bIsSigned;
	@XmlElement
	private boolean bIsUnsigned;

	public ASTSimpleDeclSpecifier(IASTSimpleDeclSpecifier s) throws Exception{
		super(s);
		declTypeExpression=new ASTNodeWrapper<ASTExpression>();
		if (s.getDeclTypeExpression()!=null){
			declTypeExpression.set(ASTExpressionFactory.create(s.getDeclTypeExpression()));
		}

		type=getType(s.getType());
		bIsComplex=s.isComplex();
		bIsImaginary=s.isImaginary();
		bIsLong=s.isLong();
		bIsLongLong=s.isLongLong();
		bIsShort=s.isShort();
		bIsSigned=s.isSigned();
		bIsUnsigned=s.isUnsigned();
	}

	public ASTSimpleDeclSpecifier(){
		declTypeExpression=new ASTNodeWrapper<ASTExpression>();
	}

	public static String getType(int i){
		if (i==IASTSimpleDeclSpecifier.t_auto){
			return "auto";
		}else if (i==IASTSimpleDeclSpecifier.t_bool){
			return "bool";
		}else if (i==IASTSimpleDeclSpecifier.t_char){
			return "char";
		}else if (i==IASTSimpleDeclSpecifier.t_char16_t){
			return "t_char16_t";
		}else if (i==IASTSimpleDeclSpecifier.t_char32_t){
			return "t_char32_t";
		}else if (i==IASTSimpleDeclSpecifier.t_decltype){
			return "t_decltype";
		}else if (i==IASTSimpleDeclSpecifier.t_double){
			return "t_double";
		}else if (i==IASTSimpleDeclSpecifier.t_float){
			return "t_float";
		}else if (i==IASTSimpleDeclSpecifier.t_float128){
			return "t_float128";
		}else if (i==IASTSimpleDeclSpecifier.t_int){
			return "t_int";
		}else if (i==IASTSimpleDeclSpecifier.t_int128){
			return "t_int128";
		}else if (i==IASTSimpleDeclSpecifier.t_typeof){
			return "t_typeof";
		}else if (i==IASTSimpleDeclSpecifier.t_unspecified){
			return "t_unspecified";
		}else if (i==IASTSimpleDeclSpecifier.t_void){
			return "t_void";
		}else if (i==IASTSimpleDeclSpecifier.t_wchar_t){
			return "t_wchar_t";
		}else {
			return "unknown";
		}
	}

	public ASTExpression getDeclTypeExpression(){
		return declTypeExpression.get();
	}

	public void setDeclTypeExpression(ASTExpression e){
		declTypeExpression.set(e);
	}

	public String getType(){
		return type;
	}

	public void setType(String k){
		type=k;
	}
	
	public boolean isComplex(){
		return bIsComplex;
	}

	public void setIsComplex(boolean b){
		bIsComplex=b;
	}

	public boolean isImaginary(){
		return bIsImaginary;
	}

	public void setIsImaginary(boolean b){
		bIsImaginary=b;
	}

	public boolean isLong(){
		return bIsLong;
	}

	public void setIsLong(boolean b){
		bIsLong=b;
	}

	public boolean isLongLong(){
		return bIsLongLong;
	}

	public void setIsLongLong(boolean b){
		bIsLongLong=b;
	}

	public boolean isShort(){
		return bIsShort;
	}

	public void setIsShort(boolean b){
		bIsShort=b;
	}

	public boolean isSigned(){
		return bIsSigned;
	}

	public void setIsSigned(boolean b){
		bIsSigned=b;
	}

	public boolean isUnsigned(){
		return bIsUnsigned;
	}

	public void setIsUnsigned(boolean b){
		bIsUnsigned=b;
	}
}
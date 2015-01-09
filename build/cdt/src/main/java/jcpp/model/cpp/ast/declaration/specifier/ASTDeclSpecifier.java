package jcpp.model.cpp.ast.declaration.specifier;

import jcpp.model.cpp.ast.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTDeclSpecifier extends ASTNode{
	@XmlElement
	private String storageClass;
	@XmlElement
	private boolean bIsConst;
	@XmlElement
	private boolean bIsInline;
	@XmlElement
	private boolean bIsRestrict;
	@XmlElement
	private boolean bIsVolatile;

	public ASTDeclSpecifier(IASTDeclSpecifier s) throws Exception{
		super(s);
		storageClass=getStorageClass(s.getStorageClass());
		bIsConst=s.isConst();
		bIsInline=s.isInline();
		bIsRestrict=s.isRestrict();
		bIsVolatile=s.isVolatile();
	}

	public ASTDeclSpecifier(){
	}

	public static String getStorageClass(int t){
		if (t==IASTDeclSpecifier.sc_auto){
			return "sc_auto";
		}else if (t==IASTDeclSpecifier.sc_extern){
			return "sc_extern";
		}else if (t==IASTDeclSpecifier.sc_mutable){
			return "sc_mutable";
		}else if (t==IASTDeclSpecifier.sc_register){
			return "sc_register";
		}else if (t==IASTDeclSpecifier.sc_static){
			return "sc_static";
		}else if (t==IASTDeclSpecifier.sc_typedef){
			return "sc_typedef";
		}else if (t==IASTDeclSpecifier.sc_unspecified){
			return "sc_unspecified";
		}else {
			return "unkown";
		} 	
	}

	public String getStorageClass(){
		return storageClass;
	}

	public void setStorageClass(String s){
		storageClass=s;
	}
	
	public boolean isConst(){
		return bIsConst;
	}

	public void setIsConst(boolean b){
		bIsConst=b;
	}

	public boolean isInline(){
		return bIsInline;
	}

	public void setIsInline(boolean b){
		bIsInline=b;
	}

	public boolean isRestrict(){
		return bIsRestrict;
	}

	public void setIsRestrict(boolean b){
		bIsRestrict=b;
	}

	public boolean isVolatile(){
		return bIsVolatile;
	}

	public void setIsVolatile(boolean b){
		bIsVolatile=b;
	}
}
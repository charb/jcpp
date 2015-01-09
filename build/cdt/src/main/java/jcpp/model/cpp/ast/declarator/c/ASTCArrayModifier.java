package jcpp.model.cpp.ast.declarator.c;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.declarator.*;
import jcpp.model.cpp.ast.name.*;
import jcpp.model.cpp.ast.attribute.*;
import jcpp.model.cpp.ast.ptr.*;
import jcpp.model.cpp.ast.expr.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.c.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCArrayModifier extends ASTArrayModifier{
	@XmlElement
	private boolean bIsConst;
	@XmlElement
	private boolean bIsRestrict;
	@XmlElement
	private boolean bIsStatic;
	@XmlElement
	private boolean bIsVariableSized;
	@XmlElement
	private boolean bIsVolatile; 

	public ASTCArrayModifier(ICASTArrayModifier p) throws Exception{
		super(p);
		bIsConst=p.isConst();
		bIsRestrict=p.isRestrict();
		bIsStatic=p.isStatic();
		bIsVariableSized=p.isVariableSized();
		bIsVolatile=p.isVolatile();
	}

	public ASTCArrayModifier(){
	}

	public boolean isConst(){
		return bIsConst;
	}

	public void setIsConst(boolean b){
		bIsConst=b;
	}

	public boolean isRestrict(){
		return bIsRestrict;
	}

	public void setIsRestrict(boolean b){
		bIsRestrict=b;
	}

	public boolean isStatic(){
		return bIsStatic;
	}

	public void setIsStatic(boolean b){
		bIsStatic=b;
	}

	public boolean isVariableSized(){
		return bIsVariableSized;
	}

	public void setIsVariableSized(boolean b){
		bIsVariableSized=b;
	}

	public boolean isVolatile(){
		return bIsVolatile;
	}

	public void setIsVolatile(boolean b){
		bIsVolatile=b;
	}
}
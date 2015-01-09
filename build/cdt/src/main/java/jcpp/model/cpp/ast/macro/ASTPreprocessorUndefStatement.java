package jcpp.model.cpp.ast.macro;

import jcpp.model.cpp.ast.*;
import org.eclipse.cdt.core.dom.ast.*;
import jcpp.model.cpp.ast.name.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTPreprocessorUndefStatement extends ASTPreprocessorStatement{
	@XmlElement
	private ASTNodeWrapper<ASTName> macroName;
	@XmlElement
	private boolean bIsActive;

	public ASTPreprocessorUndefStatement(IASTPreprocessorUndefStatement p) throws Exception{
		super(p);
		macroName=new ASTNodeWrapper<ASTName>();
		if (p.getMacroName()!=null){
			macroName.set(ASTNameFactory.create(p.getMacroName()));
		}
		bIsActive=p.isActive();
	}

	public ASTPreprocessorUndefStatement(){
		macroName=new ASTNodeWrapper<ASTName>();
	}

	public ASTName getMacroName(){
		return macroName.get();
	}

	public void setMacroName(ASTName n){
		macroName.set(n);
	}

	public boolean isActive(){
		return bIsActive;
	}

	public void setIsActive(boolean b){
		bIsActive=b;
	}
}
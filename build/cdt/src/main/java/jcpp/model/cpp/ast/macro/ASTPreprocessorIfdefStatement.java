package jcpp.model.cpp.ast.macro;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.name.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTPreprocessorIfdefStatement extends ASTPreprocessorStatement{
	@XmlElement
	private String condition;
	@XmlElement
	private boolean bTaken;
	@XmlElement
	private ASTNodeWrapper<ASTName> macroReference;

	public ASTPreprocessorIfdefStatement(IASTPreprocessorIfdefStatement p) throws Exception{
		super(p);
		condition=new String(p.getCondition());
		bTaken=p.taken();

		macroReference=new ASTNodeWrapper<ASTName>();
		if (p.getMacroReference()!=null){
			macroReference.set(ASTNameFactory.create(p.getMacroReference()));
		}
	}

	public ASTPreprocessorIfdefStatement(){
		macroReference=new ASTNodeWrapper<ASTName>();
	}

	public String getCondition(){
		return condition;
	}

	public void setCondition(String c){
		condition=c;
	}

	public boolean isTaken(){
		return bTaken;
	}

	public void setTaken(boolean b){
		bTaken=b;
	}

	public ASTName getMacroReference(){
		return macroReference.get();
	}

	public void setMacroReference(ASTName n){
		macroReference.set(n);
	}
}
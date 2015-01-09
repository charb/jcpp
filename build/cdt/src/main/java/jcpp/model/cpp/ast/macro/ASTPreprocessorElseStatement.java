package jcpp.model.cpp.ast.macro;

import jcpp.model.cpp.ast.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTPreprocessorElseStatement extends ASTPreprocessorStatement{
	@XmlElement
	private boolean bTaken;

	public ASTPreprocessorElseStatement(IASTPreprocessorElseStatement p) throws Exception{
		super(p);
		bTaken=p.taken();
	}

	public ASTPreprocessorElseStatement(){
	}

	public boolean isTaken(){
		return bTaken;
	}

	public void setTaken(boolean b){
		bTaken=b;
	}
}
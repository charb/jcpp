package jcpp.model.cpp.ast.macro;

import jcpp.model.cpp.ast.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTPreprocessorPragmaStatement extends ASTPreprocessorStatement{
	@XmlElement
	private String message;
	@XmlElement
	private boolean bIsPragmaOperator;

	public ASTPreprocessorPragmaStatement(IASTPreprocessorPragmaStatement p) throws Exception{
		super(p);
		message=new String(p.getMessage());
		bIsPragmaOperator=p.isPragmaOperator();
	}

	public ASTPreprocessorPragmaStatement(){
	}

	public String getMessage(){
		return message;
	}

	public void setMessage(String c){
		message=c;
	}

	public boolean isPragmaOperator(){
		return bIsPragmaOperator;
	}

	public void setIsPragmaOperator(boolean b){
		bIsPragmaOperator=b;
	}
}
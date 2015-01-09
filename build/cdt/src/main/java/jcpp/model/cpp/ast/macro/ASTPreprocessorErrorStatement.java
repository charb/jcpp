package jcpp.model.cpp.ast.macro;

import jcpp.model.cpp.ast.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTPreprocessorErrorStatement extends ASTPreprocessorStatement{
	@XmlElement
	private String message;

	public ASTPreprocessorErrorStatement(IASTPreprocessorErrorStatement p) throws Exception{
		super(p);
		message=new String(p.getMessage());
	}

	public ASTPreprocessorErrorStatement(){
	}

	public String getMessage(){
		return message;
	}

	public void setMessage(String c){
		message=c;
	}
}
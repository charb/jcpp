package jcpp.model.cpp.ast.macro;

import jcpp.model.cpp.ast.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTPreprocessorEndifStatement extends ASTPreprocessorStatement{

	public ASTPreprocessorEndifStatement(IASTPreprocessorEndifStatement p) throws Exception{
		super(p);
	}

	public ASTPreprocessorEndifStatement(){
	}
}
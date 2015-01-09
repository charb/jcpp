package jcpp.model.cpp.ast.macro;

import jcpp.model.cpp.ast.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTPreprocessorObjectStyleMacroDefinition extends ASTPreprocessorMacroDefinition{

	public ASTPreprocessorObjectStyleMacroDefinition(IASTPreprocessorObjectStyleMacroDefinition p) throws Exception{
		super(p);
	}

	public ASTPreprocessorObjectStyleMacroDefinition(){
	}
}
package jcpp.model.cpp.ast.macro;

import jcpp.model.cpp.ast.*;
import org.eclipse.cdt.core.dom.ast.*;
import java.util.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTPreprocessorFunctionStyleMacroDefinition extends ASTPreprocessorMacroDefinition{
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTFunctionStyleMacroParameter> parameters;

	public ASTPreprocessorFunctionStyleMacroDefinition(IASTPreprocessorFunctionStyleMacroDefinition p) throws Exception{
		super(p);
		parameters=new ArrayList<ASTFunctionStyleMacroParameter>();
		if (p.getParameters()!=null){
			for (IASTFunctionStyleMacroParameter mp : p.getParameters()){
				parameters.add(new ASTFunctionStyleMacroParameter(mp));
			}
		}
	}

	public ASTPreprocessorFunctionStyleMacroDefinition(){
	}

	public List<ASTFunctionStyleMacroParameter> getParameters(){
		return parameters;
	}

	public void addParameter(ASTFunctionStyleMacroParameter p){
		parameters.add(p);
	}
}
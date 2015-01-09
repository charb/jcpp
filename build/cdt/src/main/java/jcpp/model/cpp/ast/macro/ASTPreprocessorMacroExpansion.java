package jcpp.model.cpp.ast.macro;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.name.*;
import org.eclipse.cdt.core.dom.ast.*;
import java.util.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTPreprocessorMacroExpansion extends ASTNode{
	@XmlElement
	private ASTNodeWrapper<ASTPreprocessorMacroDefinition> macroDefinition;
	@XmlElement
	private ASTNodeWrapper<ASTName> macroReference;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTName> nestedMacroReferences;

	public ASTPreprocessorMacroExpansion(IASTPreprocessorMacroExpansion p) throws Exception{
		super(p);
		macroDefinition=new ASTNodeWrapper<ASTPreprocessorMacroDefinition>();
		if (p.getMacroDefinition()!=null){
			macroDefinition.set((ASTPreprocessorMacroDefinition)ASTPreprocessorStatementFactory.create(p.getMacroDefinition()));
		}

		macroReference=new ASTNodeWrapper<ASTName>();
		if (p.getMacroReference()!=null){
			macroReference.set(ASTNameFactory.create(p.getMacroReference()));
		}
		
		nestedMacroReferences=new ArrayList<ASTName>();
		if (p.getNestedMacroReferences()!=null){
			for (IASTName n : p.getNestedMacroReferences()){
				nestedMacroReferences.add(ASTNameFactory.create(n));
			}
		}
	}

	public ASTPreprocessorMacroExpansion(){
		macroDefinition=new ASTNodeWrapper<ASTPreprocessorMacroDefinition>();
		macroReference=new ASTNodeWrapper<ASTName>();
	}

	public ASTPreprocessorMacroDefinition getMacroDefinition(){
		return macroDefinition.get();
	}

	public void setMacroDefinition(ASTPreprocessorMacroDefinition c){
		macroDefinition.set(c);
	}

	public ASTName getMacroReference(){
		return macroReference.get();
	}

	public void setMacroReference(ASTName f){
		macroReference.set(f);
	}

	public List<ASTName> getNestedMacroReferences(){
		return nestedMacroReferences;
	}

	public void addNestedMacroReference(ASTName n){
		nestedMacroReferences.add(n);
	}
}
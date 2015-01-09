package jcpp.model.cpp.ast.macro;

import jcpp.model.cpp.ast.*;
import org.eclipse.cdt.core.dom.ast.*;
import jcpp.model.cpp.ast.name.*;
import jcpp.model.cpp.ast.location.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTPreprocessorMacroDefinition extends ASTPreprocessorStatement{
	@XmlElement
	private String expansion;
	@XmlElement
	private ASTNodeWrapper<ASTFileLocation> expansionLocation;
	@XmlElement
	private ASTNodeWrapper<ASTName> name;
	@XmlElement
	private boolean bIsActive;

	public ASTPreprocessorMacroDefinition(IASTPreprocessorMacroDefinition p) throws Exception{
		super(p);
		expansion=p.getExpansion();

		expansionLocation=new ASTNodeWrapper<ASTFileLocation>();
		if (p.getExpansionLocation()!=null){
			expansionLocation.set((ASTFileLocation)ASTNodeLocationFactory.create(p.getExpansionLocation()));
		}

		name=new ASTNodeWrapper<ASTName>();
		if (p.getName()!=null){
			name.set(ASTNameFactory.create(p.getName()));
		}
		bIsActive=p.isActive();
	}

	public ASTPreprocessorMacroDefinition(){
		expansionLocation=new ASTNodeWrapper<ASTFileLocation>();
		name=new ASTNodeWrapper<ASTName>();
	}

	public String getExpansion(){
		return expansion;
	}

	public void setExpansion(String c){
		expansion=c;
	}

	public ASTFileLocation getExpansionLocation(){
		return expansionLocation.get();
	}

	public void setExpansionLocation(ASTFileLocation f){
		expansionLocation.set(f);
	}

	public ASTName getName(){
		return name.get();
	}

	public void setName(ASTName n){
		name.set(n);
	}

	public boolean isActive(){
		return bIsActive;
	}

	public void setIsActive(boolean b){
		bIsActive=b;
	}
}
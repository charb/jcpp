package jcpp.model.cpp.ast.declaration.specifier;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.declaration.*;
import jcpp.model.cpp.ast.name.*;
import org.eclipse.cdt.core.dom.ast.*;
import java.util.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTEnumerationSpecifier extends ASTDeclSpecifier{
	@XmlElement
	private ASTNodeWrapper<ASTName> name;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTEnumerator> enumerators; 

	public ASTEnumerationSpecifier(IASTEnumerationSpecifier s) throws Exception{
		super(s);
		name=new ASTNodeWrapper<ASTName>();
		if (s.getName()!=null){
			name.set(ASTNameFactory.create(s.getName()));
		}
		enumerators=new ArrayList<ASTEnumerator>();
		if (s.getEnumerators()!=null){
			for (IASTEnumerationSpecifier.IASTEnumerator e : s.getEnumerators()){
				enumerators.add(new ASTEnumerator(e));
			}
		}
	}

	public ASTEnumerationSpecifier(){
		name=new ASTNodeWrapper<ASTName>();
	}

	public ASTName getName(){
		return name.get();
	}

	public void setName(ASTName n){
		name.set(n);
	}

	public List<ASTEnumerator> getEnumerators(){
		return enumerators;
	}

	public void addEnumerator(ASTEnumerator e){
		enumerators.add(e);
	}
}
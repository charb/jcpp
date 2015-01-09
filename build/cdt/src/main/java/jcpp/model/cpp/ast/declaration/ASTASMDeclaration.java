package jcpp.model.cpp.ast.declaration;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.stmt.*;
import jcpp.model.cpp.ast.declarator.*;
import jcpp.model.cpp.ast.declaration.specifier.*;
import org.eclipse.cdt.core.dom.ast.*;
import java.util.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTASMDeclaration extends ASTDeclaration{
	@XmlElement
	private String assembly;

	public ASTASMDeclaration(IASTASMDeclaration d) throws Exception{
		super(d);
		assembly=d.getAssembly();
	}

	public ASTASMDeclaration(){
	}

	public String getAssembly(){
		return assembly;
	}

	public void setAssembly(String a){
		assembly=a;
	}
}
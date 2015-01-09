package jcpp.model.cpp.ast.declaration.cpp;

import jcpp.model.cpp.ast.declaration.*;
import jcpp.model.cpp.ast.name.*;
import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.declarator.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import java.util.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPNamespaceAlias extends ASTDeclaration{
	@XmlElement
	private ASTNodeWrapper<ASTName> alias;
	@XmlElement
	private ASTNodeWrapper<ASTName> mappingName;

	public ASTCPPNamespaceAlias(ICPPASTNamespaceAlias d) throws Exception{
		super(d);
		alias=new ASTNodeWrapper<ASTName>();
		if (d.getAlias()!=null){
			alias.set(ASTNameFactory.create(d.getAlias()));
		}

		mappingName=new ASTNodeWrapper<ASTName>();
		if (d.getMappingName()!=null){
			mappingName.set(ASTNameFactory.create(d.getMappingName()));
		}
	}

	public ASTCPPNamespaceAlias(){
		alias=new ASTNodeWrapper<ASTName>();
		mappingName=new ASTNodeWrapper<ASTName>();
	}

	public ASTName getAlias(){
		return alias.get();
	}

	public void setAlias(ASTName n){
		alias.set(n);
	}

	public ASTName getMappingName(){
		return mappingName.get();
	}

	public void setMappingName(ASTName n){
		mappingName.set(n);
	}
}
package jcpp.model.cpp.ast.name.cpp;

import jcpp.model.cpp.ast.name.*;
import jcpp.model.cpp.ast.declaration.specifier.*;
import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.location.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import java.util.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPQualifiedName extends ASTCPPName{
	@XmlElement
	private ASTNodeWrapper<ASTName> lastName;
	@XmlAttribute
	private boolean bIsConversionOrOperator;
	@XmlAttribute
	private boolean bIsFullyQualified;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTNode> qualifier;//TODO ASTDeclSpecifier
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTNode> allSegments;//TODO ASTDeclSpecifier

	public ASTCPPQualifiedName(ICPPASTQualifiedName name) throws Exception{
		super(name);
		allSegments=new ArrayList<ASTNode>();
		if (name.getAllSegments()!=null){
			for (ICPPASTNameSpecifier s : name.getAllSegments()){
				allSegments.add((ASTNode)ASTNodeFactory.create(s));
			}
		}

		lastName=new ASTNodeWrapper<ASTName>();
		if (name.getLastName()!=null){
			lastName.set(ASTNameFactory.create(name.getLastName()));
		}

		qualifier=new ArrayList<ASTNode>();
		if (name.getQualifier()!=null){
			for (ICPPASTNameSpecifier s : name.getQualifier()){
				qualifier.add((ASTNode)ASTNodeFactory.create(s));
			}
		}

		bIsConversionOrOperator=name.isConversionOrOperator();
		bIsFullyQualified=name.isFullyQualified();
	}

	public ASTCPPQualifiedName(){
		lastName=new ASTNodeWrapper<ASTName>();
	}

	public List<ASTNode> getAllSegments(){
		return allSegments;
	}

	public void addSegment(ASTNode d){
		allSegments.add(d);
	}

	public ASTName getLastName(){
		return lastName.get();
	}

	public void setLastName(ASTName n){
		lastName.set(n);
	}

	public List<ASTNode> getQualifier(){
		return qualifier;
	}

	public void addQualifier(ASTNode d){
		qualifier.add(d);
	}

	public boolean isConversionOrOperator(){
		return bIsConversionOrOperator;
	}

	public void setIsConversionOrOperator(boolean b){
		bIsConversionOrOperator=b;
	}

	public boolean isFullyQualified(){
		return bIsFullyQualified;
	}

	public void setIsFullyQualified(boolean b){
		bIsFullyQualified=b;
	}
}
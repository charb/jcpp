package jcpp.model.cpp.ast.declarator;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.name.*;
import jcpp.model.cpp.ast.ptr.*;
import jcpp.model.cpp.ast.declaration.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTStandardFunctionDeclarator extends ASTFunctionDeclarator{
	@XmlElement
	private boolean bTakesVarArgs;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTParameterDeclaration> parameters;	

	public ASTStandardFunctionDeclarator(IASTStandardFunctionDeclarator decl) throws Exception{
		super(decl);
		parameters=new ArrayList<ASTParameterDeclaration>();
		if (decl.getParameters()!=null){
			for (IASTParameterDeclaration d : decl.getParameters()){
				parameters.add((ASTParameterDeclaration)ASTDeclarationFactory.create(d));
			}
		}
		bTakesVarArgs=decl.takesVarArgs();
	}

	public ASTStandardFunctionDeclarator(){
	}

	public List<ASTParameterDeclaration> getParameters(){
		return parameters;
	}

	public void addParameter(ASTParameterDeclaration d){
		parameters.add(d);
	}

	public boolean takesVarArgs(){
		return bTakesVarArgs;
	}

	public void setTakesVarArgs(boolean b){
		bTakesVarArgs=b;
	}
}
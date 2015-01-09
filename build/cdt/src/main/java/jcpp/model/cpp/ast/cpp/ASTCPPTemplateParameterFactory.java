package jcpp.model.cpp.ast.cpp;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.declaration.cpp.*;
import jcpp.model.cpp.ast.attribute.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import java.util.*;

public class ASTCPPTemplateParameterFactory{

	public static void fillClasses(List<Class> c) throws Exception{
		c.add(ASTCPPTemplatedTypeTemplateParameter.class);
		c.add(ASTCPPSimpleTypeTemplateParameter.class);
		c.add(ASTCPPParameterDeclaration.class);
		c.add(ASTCPPTemplateParameter.class);
	}

	public static ASTNode create(ICPPASTTemplateParameter p) throws Exception{
		if (p instanceof ICPPASTTemplatedTypeTemplateParameter){
			return new ASTCPPTemplatedTypeTemplateParameter((ICPPASTTemplatedTypeTemplateParameter)p);

		}else if (p instanceof ICPPASTSimpleTypeTemplateParameter){
			return new ASTCPPSimpleTypeTemplateParameter((ICPPASTSimpleTypeTemplateParameter)p);

		}else if (p instanceof ICPPASTParameterDeclaration){
			return new ASTCPPParameterDeclaration((ICPPASTParameterDeclaration)p);

		}else{
			return new ASTCPPTemplateParameter(p);
		}
	}
}
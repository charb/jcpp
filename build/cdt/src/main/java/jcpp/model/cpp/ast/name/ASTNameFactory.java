package jcpp.model.cpp.ast.name;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.name.cpp.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import java.util.*;

public class ASTNameFactory{

	public static void fillClasses(List<Class> c){
		c.add(ASTCPPConversionName.class);
		c.add(ASTCPPOperatorName.class);
		c.add(ASTCPPQualifiedName.class);
		c.add(ASTCPPTemplateId.class);
		c.add(ASTImplicitName.class);
		c.add(ASTCPPName.class);
		c.add(ASTName.class);
	}

	public static ASTName create(IASTName name) throws Exception{
		if (name instanceof ICPPASTConversionName){
			return new ASTCPPConversionName((ICPPASTConversionName)name);

		}else if (name instanceof ICPPASTOperatorName){
			return new ASTCPPOperatorName((ICPPASTOperatorName)name);

		}else if (name instanceof ICPPASTQualifiedName){
			return new ASTCPPQualifiedName((ICPPASTQualifiedName)name);

		}else if (name instanceof ICPPASTTemplateId){
			return new ASTCPPTemplateId((ICPPASTTemplateId)name);

		}else if (name instanceof IASTImplicitName){
			return new ASTImplicitName((IASTImplicitName)name);

		}else if (name instanceof ICPPASTName){
			return new ASTCPPName((ICPPASTName)name);

		}else{
			return new ASTName(name);
		}
	}
}
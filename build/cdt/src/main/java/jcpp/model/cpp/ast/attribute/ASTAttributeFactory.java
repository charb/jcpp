package jcpp.model.cpp.ast.attribute;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.attribute.cpp.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import java.util.*;

public class ASTAttributeFactory{

	public static void fillClasses(List<Class> c){
		c.add(ASTCPPAttribute.class);
		c.add(ASTAttribute.class);
	}

	public static ASTAttribute create(IASTAttribute decl) throws Exception{
		if (decl instanceof ICPPASTAttribute){
			return new ASTCPPAttribute((ICPPASTAttribute)decl);
		
		}else{
			return new ASTAttribute(decl);
		}
	}
}
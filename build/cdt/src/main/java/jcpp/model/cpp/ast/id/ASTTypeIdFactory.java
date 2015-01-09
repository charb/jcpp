package jcpp.model.cpp.ast.id;

import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.declarator.*;
import jcpp.model.cpp.ast.declaration.specifier.*;
import jcpp.model.cpp.ast.id.cpp.*;
import java.util.*;

public class ASTTypeIdFactory{

	public static void fillClasses(List<Class> c){
		c.add(ASTCPPTypeId.class);
		c.add(ASTProblemTypeId.class);
		c.add(ASTTypeId.class);
	}

	public static ASTTypeId create(IASTTypeId typeId) throws Exception{
		if (typeId instanceof ICPPASTTypeId){
			return new ASTCPPTypeId((ICPPASTTypeId)typeId);

		}else if (typeId instanceof IASTProblemTypeId){
			return new ASTProblemTypeId((IASTProblemTypeId)typeId);

		}else{
			return new ASTTypeId(typeId);
		}
	}
}
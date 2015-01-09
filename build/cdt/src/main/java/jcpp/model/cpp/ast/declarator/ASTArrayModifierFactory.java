package jcpp.model.cpp.ast.declarator;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.name.*;
import jcpp.model.cpp.ast.attribute.*;
import jcpp.model.cpp.ast.ptr.*;
import jcpp.model.cpp.ast.expr.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.c.*;
import jcpp.model.cpp.ast.declarator.c.*;
import java.util.*;

public class ASTArrayModifierFactory{

	public static void fillClasses(List<Class> c){
		c.add(ASTCArrayModifier.class);
		c.add(ASTArrayModifier.class);
	}

	public static ASTArrayModifier create(IASTArrayModifier decl) throws Exception{
		if (decl instanceof ICASTArrayModifier){
			return new ASTCArrayModifier((ICASTArrayModifier)decl);
		}else{
			return new ASTArrayModifier(decl);
		}
	}
}
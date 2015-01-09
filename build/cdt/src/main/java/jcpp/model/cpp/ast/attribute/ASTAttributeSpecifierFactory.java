package jcpp.model.cpp.ast.attribute;

import jcpp.model.cpp.ast.*;
import org.eclipse.cdt.core.dom.ast.*;
import jcpp.model.cpp.ast.attribute.cpp.*;
import java.util.*;

public class ASTAttributeSpecifierFactory{

	public static void fillClasses(List<Class> c) throws Exception{
		c.add(ASTAttributeSpecifier.class);
	}

	public static ASTAttributeSpecifier create(IASTAttributeSpecifier decl) throws Exception{
		return new ASTAttributeSpecifier(decl);
	}
}
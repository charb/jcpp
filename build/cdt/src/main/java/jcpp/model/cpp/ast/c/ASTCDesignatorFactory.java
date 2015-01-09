package jcpp.model.cpp.ast.c;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.attribute.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.c.*;
import java.util.*;

public class ASTCDesignatorFactory{

	public static void fillClasses(List<Class> c) throws Exception{
		c.add(ASTCArrayDesignator.class);
		c.add(ASTCFieldDesignator.class);
		c.add(ASTCDesignator.class);
	}

	public static ASTCDesignator create(ICASTDesignator p) throws Exception{
		if (p instanceof ICASTArrayDesignator){
			return new ASTCArrayDesignator((ICASTArrayDesignator)p);

		}else if (p instanceof ICASTFieldDesignator){
			return new ASTCFieldDesignator((ICASTFieldDesignator)p);

		}else{
			return new ASTCDesignator(p);
		}
	}
}
package jcpp.model.cpp.ast.location;

import org.eclipse.cdt.core.dom.ast.*;
import java.util.*;

public class ASTNodeLocationFactory{

	public static void fillClasses(List<Class> c){
		c.add(ASTImageLocation.class);
		c.add(ASTFileLocation.class);
		c.add(ASTMacroExpansionLocation.class);
		c.add(ASTNodeLocation.class);
	}

	public static ASTNodeLocation create(IASTNodeLocation nodeLocation) throws Exception{
		if (nodeLocation instanceof IASTImageLocation){
			return new ASTImageLocation((IASTImageLocation)nodeLocation);

		}else if (nodeLocation instanceof IASTFileLocation){
			return new ASTFileLocation((IASTFileLocation)nodeLocation);

		}else if (nodeLocation instanceof IASTMacroExpansionLocation){
			return new ASTMacroExpansionLocation((IASTMacroExpansionLocation)nodeLocation);

		}else{
			return new ASTNodeLocation(nodeLocation);
		}
	}
}
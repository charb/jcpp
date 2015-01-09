package jcpp.model.cpp.ast.macro;

import jcpp.model.cpp.ast.*;
import org.eclipse.cdt.core.dom.ast.*;
import java.util.*;

public class ASTPreprocessorStatementFactory{

	public static void fillClasses(List<Class> c){
		c.add(ASTPreprocessorUndefStatement.class);
		c.add(ASTPreprocessorPragmaStatement.class);
		c.add(ASTPreprocessorObjectStyleMacroDefinition.class);
		c.add(ASTPreprocessorIncludeStatement.class);
		c.add(ASTPreprocessorIfStatement.class);
		c.add(ASTPreprocessorIfndefStatement.class);
		c.add(ASTPreprocessorIfdefStatement.class);
		c.add(ASTPreprocessorFunctionStyleMacroDefinition.class);
		c.add(ASTPreprocessorErrorStatement.class);
		c.add(ASTPreprocessorEndifStatement.class);
		c.add(ASTPreprocessorElseStatement.class);
		c.add(ASTPreprocessorElifStatement.class);
		c.add(ASTPreprocessorMacroDefinition.class);
		c.add(ASTPreprocessorStatement.class);
	}

	public static ASTPreprocessorStatement create(IASTPreprocessorStatement p) throws Exception{
		if (p instanceof IASTPreprocessorUndefStatement){
			return new ASTPreprocessorUndefStatement((IASTPreprocessorUndefStatement)p);
		
		}else if (p instanceof IASTPreprocessorPragmaStatement){
			return new ASTPreprocessorPragmaStatement((IASTPreprocessorPragmaStatement)p);

		}else if (p instanceof IASTPreprocessorObjectStyleMacroDefinition){
			return new ASTPreprocessorObjectStyleMacroDefinition((IASTPreprocessorObjectStyleMacroDefinition)p);
			
		}else if (p instanceof IASTPreprocessorIncludeStatement){
			return new ASTPreprocessorIncludeStatement((IASTPreprocessorIncludeStatement)p);
			
		}else if (p instanceof IASTPreprocessorIfStatement){
			return new ASTPreprocessorIfStatement((IASTPreprocessorIfStatement)p);
			
		}else if (p instanceof IASTPreprocessorIfndefStatement){
			return new ASTPreprocessorIfndefStatement((IASTPreprocessorIfndefStatement)p);
			
		}else if (p instanceof IASTPreprocessorIfdefStatement){
			return new ASTPreprocessorIfdefStatement((IASTPreprocessorIfdefStatement)p);
			
		}else if (p instanceof IASTPreprocessorFunctionStyleMacroDefinition){
			return new ASTPreprocessorFunctionStyleMacroDefinition((IASTPreprocessorFunctionStyleMacroDefinition)p);
			
		}else if (p instanceof IASTPreprocessorErrorStatement){
			return new ASTPreprocessorErrorStatement((IASTPreprocessorErrorStatement)p);
			
		}else if (p instanceof IASTPreprocessorEndifStatement){
			return new ASTPreprocessorEndifStatement((IASTPreprocessorEndifStatement)p);
			
		}else if (p instanceof IASTPreprocessorElseStatement){
			return new ASTPreprocessorElseStatement((IASTPreprocessorElseStatement)p);
			
		}else if (p instanceof IASTPreprocessorElifStatement){
			return new ASTPreprocessorElifStatement((IASTPreprocessorElifStatement)p);
			
		}else if (p instanceof IASTPreprocessorMacroDefinition){
			return new ASTPreprocessorMacroDefinition((IASTPreprocessorMacroDefinition)p);
			
		}else{
			return new ASTPreprocessorStatement(p);
		}
	}
}
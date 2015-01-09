package jcpp.model.cpp.ast.stmt;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.stmt.cpp.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import java.util.*;

public class ASTStatementFactory{

	public static void fillClasses(List<Class> c){
		c.add(ASTCPPCatchHandler.class);
		c.add(ASTCPPForStatement.class);
		c.add(ASTCPPIfStatement.class);
		c.add(ASTCPPRangeBasedForStatement.class);
		c.add(ASTCPPSwitchStatement.class);
		c.add(ASTCPPTryBlockStatement.class);
		c.add(ASTCPPWhileStatement.class);
		c.add(ASTCompoundStatement.class);
		c.add(ASTBreakStatement.class);
		c.add(ASTCaseStatement.class);
		c.add(ASTContinuteStatement.class);
		c.add(ASTDefaultStatement.class);
		c.add(ASTDoStatement.class);
		c.add(ASTGotoStatement.class);
		c.add(ASTLabelStatement.class);
		c.add(ASTNullStatement.class);
		c.add(ASTProblemStatement.class);
		c.add(ASTSwitchStatement.class);
		c.add(ASTDeclarationStatement.class);
		c.add(ASTExpressionStatement.class);
		c.add(ASTForStatement.class);
		c.add(ASTIfStatement.class);
		c.add(ASTNullStatement.class);
		c.add(ASTReturnStatement.class);
		c.add(ASTWhileStatement.class);
	}

	public static ASTStatement create(IASTStatement s) throws Exception{
		if (s instanceof ICPPASTCatchHandler){
			return new ASTCPPCatchHandler((ICPPASTCatchHandler)s);

		}else if (s instanceof ICPPASTForStatement){
			return new ASTCPPForStatement((ICPPASTForStatement)s);

		}else if (s instanceof ICPPASTIfStatement){
			return new ASTCPPIfStatement((ICPPASTIfStatement)s);

		}else if (s instanceof ICPPASTRangeBasedForStatement){
			return new ASTCPPRangeBasedForStatement((ICPPASTRangeBasedForStatement)s);

		}else if (s instanceof ICPPASTSwitchStatement){
			return new ASTCPPSwitchStatement((ICPPASTSwitchStatement)s);

		}else if (s instanceof ICPPASTTryBlockStatement){
			return new ASTCPPTryBlockStatement((ICPPASTTryBlockStatement)s);

		}else if (s instanceof ICPPASTWhileStatement){
			return new ASTCPPWhileStatement((ICPPASTWhileStatement)s);

		}else if (s instanceof IASTCompoundStatement){
			return new ASTCompoundStatement((IASTCompoundStatement)s);

		}else if (s instanceof IASTBreakStatement){
			return new ASTBreakStatement((IASTBreakStatement)s);

		}else if (s instanceof IASTCaseStatement){
			return new ASTCaseStatement((IASTCaseStatement)s);

		}else if (s instanceof IASTContinueStatement){
			return new ASTContinuteStatement((IASTContinueStatement)s);

		}else if (s instanceof IASTDefaultStatement){
			return new ASTDefaultStatement((IASTDefaultStatement)s);

		}else if (s instanceof IASTDoStatement){
			return new ASTDoStatement((IASTDoStatement)s);

		}else if (s instanceof IASTGotoStatement){
			return new ASTGotoStatement((IASTGotoStatement)s);

		}else if (s instanceof IASTLabelStatement){
			return new ASTLabelStatement((IASTLabelStatement)s);

		}else if (s instanceof IASTNullStatement){
			return new ASTNullStatement((IASTNullStatement)s);

		}else if (s instanceof IASTProblemStatement){
			return new ASTProblemStatement((IASTProblemStatement)s);

		}else if (s instanceof IASTSwitchStatement){
			return new ASTSwitchStatement((IASTSwitchStatement)s);

		}else if (s instanceof IASTDeclarationStatement){
			return new ASTDeclarationStatement((IASTDeclarationStatement)s);

		}else if (s instanceof IASTExpressionStatement){
			return new ASTExpressionStatement((IASTExpressionStatement)s);

		}else if (s instanceof IASTForStatement){
			return new ASTForStatement((IASTForStatement)s);

		}else if (s instanceof IASTIfStatement){
			return new ASTIfStatement((IASTIfStatement)s);

		}else if (s instanceof IASTNullStatement){
			return new ASTNullStatement((IASTNullStatement)s);

		}else if (s instanceof IASTReturnStatement){
			return new ASTReturnStatement((IASTReturnStatement)s);

		}else if (s instanceof IASTWhileStatement){
			return new ASTWhileStatement((IASTWhileStatement)s);

		}else {
			throw new Exception("unknown statement "+s);
		}
	}
}
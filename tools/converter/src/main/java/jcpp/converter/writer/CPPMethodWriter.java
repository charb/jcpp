package jcpp.converter.writer;

import jcpp.converter.strategies.*;
import jcpp.converter.model.*;
import jcpp.converter.model.stmt.*;
import jcpp.converter.model.expression.*;
import jcpp.converter.model.body.*;
import java.io.*;
import java.util.*;

public class CPPMethodWriter{
	protected IStrategies strategies;
	protected CPPTypeWriter typeWriter;

	public CPPMethodWriter(IStrategies strategies){
		this.strategies=strategies;
		this.typeWriter=new CPPTypeWriter(strategies);
	}

	public void write(String ident, CPPMethod method, StringBuffer sb) throws Exception{
		CPPBlockStatement stmt=method.getBody();
		if (stmt!=null){
			write(ident,method,stmt,sb);
		}
	}

	protected void write(String ident,CPPMethod method,CPPStatement stmt, StringBuffer sb) throws Exception{
		if (stmt instanceof CPPBlockStatement){
			CPPBlockStatement bc=(CPPBlockStatement)stmt;
			if (bc.getStatements().size()>0){
				for (CPPStatement s : bc.getStatements()){
					write(ident,method,s,sb);
				}
			}

		}else if (stmt instanceof CPPAssertStatement){
			//TODO add dependency + use CPPCallMethodExpression
			CPPAssertStatement bc=(CPPAssertStatement)stmt;
			sb.append(ident).append("if (!(");
			write("",method,bc.getCheck(),sb);
			sb.append(")){").append(System.lineSeparator());
			sb.append(ident+"    ").append("throw new JException(");
			write("",method,bc.getMessage(),sb);
			sb.append(");").append(System.lineSeparator());
			sb.append(ident).append("}").append(System.lineSeparator());

		}else if (stmt instanceof CPPBreakStatement){
			CPPBreakStatement bc=(CPPBreakStatement)stmt;
			if (bc.getId()!=null){
				throw new RuntimeException("Not handling break with id "+bc.getId());
			}
			sb.append(ident).append("break;").append(System.lineSeparator());

		}else if (stmt instanceof CPPCatchClauseStatement){
			CPPCatchClauseStatement bc=(CPPCatchClauseStatement)stmt;
			bc.getCatchBlock();
			bc.getExcept();

		}else if (stmt instanceof CPPContinueStatement){
			CPPContinueStatement bc=(CPPContinueStatement)stmt;
			if (bc.getId()!=null){
				throw new RuntimeException("Not handling continue with id "+bc.getId());
			}
			sb.append(ident).append("continue;").append(System.lineSeparator());

		}else if (stmt instanceof CPPDoStatement){
			CPPDoStatement bc=(CPPDoStatement)stmt;
			sb.append(ident).append("do {").append(System.lineSeparator());
			write(ident+"    ",method,bc.getBody(),sb);
			sb.append(ident).append("} while (");
			write("",method,bc.getCondition(),sb);
			sb.append(");").append(System.lineSeparator());

		}else if (stmt instanceof CPPEmptyStatement){
			CPPEmptyStatement bc=(CPPEmptyStatement)stmt;
			sb.append(ident).append(";").append(System.lineSeparator());
			
		}else if (stmt instanceof CPPExplicitConstructorInvocationStatement){
			CPPExplicitConstructorInvocationStatement bc=(CPPExplicitConstructorInvocationStatement)stmt;
			bc.getExpression();
			bc.isThis();
			if (bc.getArgs()!=null){
				for (CPPExpression ee : bc.getArgs()){
				}
			}
			if (bc.getTypeArgs()!=null){
				for (CPPType ee : bc.getTypeArgs()){
				}
			}

		}else if (stmt instanceof CPPExpressionStatement){
			CPPExpressionStatement bc=(CPPExpressionStatement)stmt;
			write(ident,method,bc.getExpression(),sb);
			sb.append(";").append(System.lineSeparator());

		}else if (stmt instanceof CPPForEachStatement){
			CPPForEachStatement bc=(CPPForEachStatement)stmt;
			sb.append(ident).append("for (JIterator* it=");//TODO bc.getVariable()
			write("",method,bc.getIterable(),sb);
			sb.append("->iterator(); it->hasNext(); it->next(){").append(System.lineSeparator());
			sb.append(bc.getVariable());
			write(ident+"    ",method,bc.getBody(),sb);
			sb.append(ident).append("}");
		
		}else if (stmt instanceof CPPForStatement){
			CPPForStatement bc=(CPPForStatement)stmt;
			sb.append(ident).append("for (");
			if (bc.getInit()!=null){
				boolean b=false;
				for (CPPExpression e : bc.getInit()){
					if (b){
						sb.append(", ");
					}
					write("",method,e,sb);
					b=true;
				}
			}
			sb.append(" ; ");
			write("",method,bc.getCompare(),sb);
			sb.append(" ; ");
			if (bc.getUpdate()!=null){
				boolean b=false;
				for (CPPExpression e : bc.getUpdate()){
					if (b){
						sb.append(", ");
					}
					write("",method,e,sb);
					b=true;
				}
			}
			sb.append("){").append(System.lineSeparator());
			write(ident+"    ",method,bc.getBody(),sb);
			sb.append(ident).append("}").append(System.lineSeparator());

		}else if (stmt instanceof CPPIfStatement){
			CPPIfStatement bc=(CPPIfStatement)stmt;
			sb.append(ident).append("if (");
			write("",method,bc.getCondition(),sb);
			sb.append(") {").append(System.lineSeparator());
			write(ident+"    ",method,bc.getThenStatement(),sb);
			sb.append(ident).append("}");
			if (bc.getElseStatement()!=null){
				sb.append("else {").append(System.lineSeparator());
				write(ident+"    ",method,bc.getElseStatement(),sb);
				sb.append(ident).append("}");
			}
			sb.append(System.lineSeparator());

		}else if (stmt instanceof CPPLabeledStatement){
			CPPLabeledStatement bc=(CPPLabeledStatement)stmt;
			bc.getLabel();
			bc.getStatement();

		}else if (stmt instanceof CPPReturnStatement){
			CPPReturnStatement bc=(CPPReturnStatement)stmt;
			sb.append(ident).append("return ");
			write("",method,bc.getExpression(),sb);
			sb.append(";").append(System.lineSeparator());

		}else if (stmt instanceof CPPSwitchEntryStatement){
			CPPSwitchEntryStatement bc=(CPPSwitchEntryStatement)stmt;
			bc.getLabel();
			bc.getStatements();

		}else if (stmt instanceof CPPSwitchStatement){
			CPPSwitchStatement bc=(CPPSwitchStatement)stmt;
			bc.getSelector();
			bc.getEntries();
			
		}else if (stmt instanceof CPPSynchronizedStatement){
			CPPSynchronizedStatement bc=(CPPSynchronizedStatement)stmt;
			sb.append(ident).append("synchronized(");
			write("",method,bc.getExpression(),sb);
			sb.append(", { ").append(System.lineSeparator());
			write(ident+"    ",method,bc.getBlockStatement(),sb);
			sb.append(ident).append("})").append(System.lineSeparator());
			
		}else if (stmt instanceof CPPThrowStatement){
			CPPThrowStatement bc=(CPPThrowStatement)stmt;
			sb.append(ident).append("throw ");
			write("",method,bc.getExpression(),sb);
			sb.append(";").append(System.lineSeparator());
			
		}else if (stmt instanceof CPPTryStatement){
			CPPTryStatement bc=(CPPTryStatement)stmt;
			bc.getFinallyBlock();
			bc.getTryBlock();
			bc.getCatchs();
			bc.getResources();

		}else if (stmt instanceof CPPTypeDeclarationStatement){
			CPPTypeDeclarationStatement bc=(CPPTypeDeclarationStatement)stmt;
			write(ident,method,bc.getTypeDeclaration(),sb);

		}else if (stmt instanceof CPPWhileStatement){
			CPPWhileStatement bc=(CPPWhileStatement)stmt;
			sb.append(ident).append("while (");
			write("",method,bc.getCondition(),sb);
			sb.append(") {").append(System.lineSeparator());
			write(ident+"    ",method,bc.getBody(),sb);
			sb.append(ident).append("}").append(System.lineSeparator());
		}
	}

	protected void write(String ident,CPPMethod method,CPPBodyDeclaration bd, StringBuffer sb) throws Exception{
		//TODO
		if (bd instanceof CPPTypeDeclaration){
			CPPTypeDeclaration td=(CPPTypeDeclaration)bd;
			if (td.getMembers()!=null){
				for (CPPBodyDeclaration b : td.getMembers()){
				}
			}
			td.getName();
			td.getModifiers();
			td.getNameExpression();

		}else if (bd instanceof CPPMethodDeclaration){
			CPPMethodDeclaration td=(CPPMethodDeclaration)bd;
			td.getArrayCount();
			td.getModifiers();
			td.getName();
			td.getBody();
			td.getNameExpression();
			for (CPPParameter p : td.getParameters()){
			}
			td.getType();
		}
	}

	protected void write(String ident,CPPMethod method,CPPExpression expr, StringBuffer sb) throws Exception{
		if (expr instanceof CPPArrayAccessExpression){
			CPPArrayAccessExpression e=(CPPArrayAccessExpression)expr;
			sb.append(ident);
			write("",method,e.getName(),sb);
			sb.append("[");
			write("",method,e.getIndex(),sb);
			sb.append("]");
			//TODO bugged, should be either get()/getInt()/...

		}else if (expr instanceof CPPArrayCreationExpression){
			CPPArrayCreationExpression e=(CPPArrayCreationExpression)expr;
			e.getArrayCount();
			e.getInitializer();
			e.getType();
			e.getDimensions();

		}else if (expr instanceof CPPArrayInitializerExpression){
			CPPArrayInitializerExpression e=(CPPArrayInitializerExpression)expr;
			e.getValues();

		}else if (expr instanceof CPPAssignExpression){
			CPPAssignExpression e=(CPPAssignExpression)expr;
			sb.append(ident);
			write("",method,e.getTarget(),sb);
			sb.append(" ").append(e.getOperator()).append(" ");
			write("",method,e.getValue(),sb);

		}else if (expr instanceof CPPBinaryExpression){
			CPPBinaryExpression e=(CPPBinaryExpression)expr;
			sb.append(ident);
			write("",method,e.getLeft(),sb);
			sb.append(" ").append(e.getOperator()).append(" ");
			write("",method,e.getRight(),sb);

		}else if (expr instanceof CPPBooleanLiteralExpression){
			CPPBooleanLiteralExpression e=(CPPBooleanLiteralExpression)expr;
			sb.append(ident).append(e.getValue());

		}else if (expr instanceof CPPCastExpression){
			CPPCastExpression e=(CPPCastExpression)expr;
			sb.append(ident).append("dynamic_cast<");
			typeWriter.write(e.getType(),sb);
			sb.append(">( ");
			write("",method,e.getExpression(),sb);
			sb.append(")");			

		}else if (expr instanceof CPPCharLiteralExpression){
			CPPCharLiteralExpression e=(CPPCharLiteralExpression)expr;
			sb.append(ident).append("\'").append(e.getValue()).append("\'");

		}else if (expr instanceof CPPClassExpression){
			CPPClassExpression e=(CPPClassExpression)expr;
			sb.append(ident);
			typeWriter.writeClazz(e.getType(),sb);

		}else if (expr instanceof CPPConditionalExpression){
			CPPConditionalExpression e=(CPPConditionalExpression)expr;
			sb.append(ident).append(" (");
			write("",method,e.getCondition(),sb);
			sb.append(" ? ");
			write("",method,e.getThenExpression(),sb);
			sb.append(" : ");
			write("",method,e.getElseExpression(),sb);
			sb.append(") ");

		}else if (expr instanceof CPPDoubleLiteralExpression){
			CPPDoubleLiteralExpression e=(CPPDoubleLiteralExpression)expr;
			sb.append(ident).append(e.getValue());

		}else if (expr instanceof CPPEnclosedExpression){
			CPPEnclosedExpression e=(CPPEnclosedExpression)expr;
			sb.append(ident).append("(");
			write("",method,e.getInner(),sb);
			sb.append(")");

		}else if (expr instanceof CPPFieldAccessExpression){
			CPPFieldAccessExpression e=(CPPFieldAccessExpression)expr;
			sb.append(ident);
			write("",method,e.getScope(),sb);
			boolean bStatic=false;

			if (e.getScope() instanceof CPPNameExpression){
				CPPNameExpression ne=(CPPNameExpression)e.getScope();
				if (method.getClazz().isType(ne.getName())){
					bStatic=true;
				}
			}

			if (bStatic){
				sb.append("::");
			}else{
				sb.append("->");
			}
			write("",method,e.getFieldExpression(),sb);

		}else if (expr instanceof CPPInstanceOfExpression){
			CPPInstanceOfExpression e=(CPPInstanceOfExpression)expr;
			sb.append(ident).append("(");
			write("",method,e.getExpression(),sb);
			sb.append(")->isInstanceOf(");
			typeWriter.writeClazz(e.getType(),sb);
			sb.append(")");

		}else if (expr instanceof CPPIntegerLiteralExpression){
			CPPIntegerLiteralExpression e=(CPPIntegerLiteralExpression)expr;
			sb.append(ident).append(e.getValue());

		}else if (expr instanceof CPPLongLiteralExpression){
			CPPLongLiteralExpression e=(CPPLongLiteralExpression)expr;
			sb.append(ident).append(e.getValue());;

		}else if (expr instanceof CPPMethodCallExpression){
			CPPMethodCallExpression e=(CPPMethodCallExpression)expr;
			sb.append(ident).append(e.getName()).append("(");
			if (e.getArgs()!=null){
				boolean b=false;
				for (CPPExpression ee : e.getArgs()){
					if (b){
						sb.append(", ");
					}
					write("",method,ee,sb);
					b=true;
				}
			}
			sb.append(")");

		}else if (expr instanceof CPPNameExpression){
			CPPNameExpression e=(CPPNameExpression)expr;
			sb.append(ident).append(e.getName());

		}else if (expr instanceof CPPNullLiteralExpression){
			CPPNullLiteralExpression e=(CPPNullLiteralExpression)expr;
			sb.append(ident).append("null");

		}else if (expr instanceof CPPObjectCreationExpression){
			CPPObjectCreationExpression e=(CPPObjectCreationExpression)expr;
			sb.append(ident).append("new ").append(e.getType().getName()).append("(");
			if (e.getArgs()!=null){
				boolean b=false;
				for (CPPExpression ee : e.getArgs()){
					if (!b){
						sb.append(",");
					}
					write("",method,ee,sb);
					b=true;
				}
			}
			sb.append(")");
			//TODO what to do? 
			//if (e.getAnonymousClassBody()!=null){
			// 	throw new RuntimeException(" cannot create an object with an anonymous body "+e);
			// }

		}else if (expr instanceof CPPQualifiedNameExpression){
			CPPQualifiedNameExpression e=(CPPQualifiedNameExpression)expr;
			e.getName();
			e.getQualifier();
			throw new RuntimeException("CPPQualifiedNameExpression== "+e+" name=="+e.getName()+" qualif="+e.getQualifier());

		}else if (expr instanceof CPPStringLiteralExpression){
			CPPStringLiteralExpression e=(CPPStringLiteralExpression)expr;
			sb.append(ident).append("\"").append(e.getValue()).append("\"");

		}else if (expr instanceof CPPSuperExpression){
			CPPSuperExpression e=(CPPSuperExpression)expr;
			e.getClassExpression();
			//TODO
			//throw new RuntimeException("CPPSuperExpression== "+e+" getClassExpression=="+e.getClassExpression());

		}else if (expr instanceof CPPThisExpression){
			CPPThisExpression e=(CPPThisExpression)expr;
			//not seemed to be filled : e.getClassExpression();
			sb.append(ident).append("this");

		}else if (expr instanceof CPPUnaryExpression){
			CPPUnaryExpression e=(CPPUnaryExpression)expr;
			sb.append(ident);
			if (e.getOperator().isLeft()){
				sb.append(e.getOperator());
			}
			write("",method,e.getExpression(),sb);
			if (!e.getOperator().isLeft()){
				sb.append(e.getOperator());
			}

		}else if (expr instanceof CPPVariableDeclarationExpression){
			CPPVariableDeclarationExpression e=(CPPVariableDeclarationExpression)expr;
			sb.append(ident);
			typeWriter.write(e.getType(),sb);
			boolean first=true;
			for (CPPVariableDeclarator var : e.getVars()){
				if (!first){
					sb.append(", ");
				}
				sb.append(" ").append(var.getId().getName()).append(" = ");
				write("",method,var.getInit(),sb);
				first=false;
			}
		}
	}
}
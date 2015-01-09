package jcpp.converter.model;

import jcpp.converter.model.stmt.*;
import jcpp.converter.model.expression.*;
import jcpp.converter.model.body.*;
import jcpp.converter.strategies.*;
import java.util.*;
import japa.parser.*;
import japa.parser.ast.*;
import japa.parser.ast.stmt.*;
import japa.parser.ast.body.*;
import japa.parser.ast.expr.*;
import japa.parser.ast.visitor.*;
import japa.parser.ast.type.*;

public class CPPModelFactory{
	
	public static CPPStatement create(IStrategies strategies,CPPMethod method,Node stmt){
		if (stmt==null){
			return null;
		}
		if (stmt instanceof AssertStmt){
			AssertStmt as=(AssertStmt)stmt;
			CPPAssertStatement cppstmt=new CPPAssertStatement(method);
			cppstmt.setCheck(create(strategies,method,as.getCheck()));
			cppstmt.setMessage(create(strategies,method,as.getMessage()));
			return cppstmt;

		}else if (stmt instanceof BlockStmt){
			BlockStmt bs=(BlockStmt)stmt;
			CPPBlockStatement cppstmt=new CPPBlockStatement(method);
			if (bs.getStmts()!=null){
				for (Statement s : bs.getStmts()){
					cppstmt.addStatement(create(strategies,method,s));
				}
			}
			return cppstmt;

		}else if (stmt instanceof BreakStmt){
			BreakStmt bs=(BreakStmt)stmt;
			CPPBreakStatement cppstmt=new CPPBreakStatement(method);
			cppstmt.setId(bs.getId());
			return cppstmt;
			
		}else if (stmt instanceof CatchClause){
			CatchClause bs=(CatchClause)stmt;
			CPPCatchClauseStatement cppstmt=new CPPCatchClauseStatement(method);
			cppstmt.setCatchBlock((CPPBlockStatement)create(strategies,method,bs.getCatchBlock()));
			cppstmt.setExcept((CPPMultiTypeParameter)create(strategies,method,bs.getExcept()));
			return cppstmt;
			
		}else if (stmt instanceof ContinueStmt){
			ContinueStmt bs=(ContinueStmt)stmt;
			CPPContinueStatement cppstmt=new CPPContinueStatement(method);
			cppstmt.setId(bs.getId());
			return cppstmt;
			
		}else if (stmt instanceof DoStmt){
			DoStmt bs=(DoStmt)stmt;
			CPPDoStatement cppstmt=new CPPDoStatement(method);
			cppstmt.setBody(create(strategies,method,bs.getBody()));
			cppstmt.setCondition(create(strategies,method,bs.getCondition()));
			return cppstmt;
			
		}else if (stmt instanceof EmptyStmt){
			EmptyStmt bs=(EmptyStmt)stmt;
			CPPEmptyStatement cppstmt=new CPPEmptyStatement(method);
			return cppstmt;

		}else if (stmt instanceof ExplicitConstructorInvocationStmt){
			ExplicitConstructorInvocationStmt bs=(ExplicitConstructorInvocationStmt)stmt;
			CPPExplicitConstructorInvocationStatement cppstmt=new CPPExplicitConstructorInvocationStatement(method);
			cppstmt.setExpression(create(strategies,method,bs.getExpr()));
			cppstmt.setIsThis(bs.isThis());
			if (bs.getArgs()!=null){
				for (Expression ee : bs.getArgs()){
					cppstmt.addArg(create(strategies,method,ee));
				}
			}
			if (bs.getTypeArgs()!=null){
				for (Type ee : bs.getTypeArgs()){
					cppstmt.addTypeArg(createType(strategies,method,ee));
				}
			}
			return cppstmt;
			
		}else if (stmt instanceof ExpressionStmt){
			ExpressionStmt bs=(ExpressionStmt)stmt;
			CPPExpressionStatement cppstmt=new CPPExpressionStatement(method);
			cppstmt.setExpression(create(strategies,method,bs.getExpression()));
			return cppstmt;
			
		}else if (stmt instanceof ForeachStmt){
			ForeachStmt bs=(ForeachStmt)stmt;
			CPPForEachStatement cppstmt=new CPPForEachStatement(method);
			cppstmt.setBody(create(strategies,method,bs.getBody()));
			cppstmt.setIterable(create(strategies,method,bs.getIterable()));
			cppstmt.setVariable((CPPVariableDeclarationExpression)create(strategies,method,bs.getVariable()));
			return cppstmt;
			
		}else if (stmt instanceof ForStmt){
			ForStmt bs=(ForStmt)stmt;
			CPPForStatement cppstmt=new CPPForStatement(method);
			cppstmt.setBody(create(strategies,method,bs.getBody()));
			cppstmt.setCompare(create(strategies,method,bs.getCompare()));
			if (bs.getInit()!=null){
				for (Expression e : bs.getInit()){
					cppstmt.addInit(create(strategies,method,e));
				}
			}
			if (bs.getUpdate()!=null){
				for (Expression e : bs.getUpdate()){
					cppstmt.addUpdate(create(strategies,method,e));
				}
			}
			return cppstmt;
			
		}else if (stmt instanceof IfStmt){
			IfStmt bs=(IfStmt)stmt;
			CPPIfStatement cppstmt=new CPPIfStatement(method);
			cppstmt.setCondition(create(strategies,method,bs.getCondition()));
			cppstmt.setElseStatement(create(strategies,method,bs.getElseStmt()));
			cppstmt.setThenStatement(create(strategies,method,bs.getThenStmt()));
			return cppstmt;
			
		}else if (stmt instanceof LabeledStmt){
			LabeledStmt bs=(LabeledStmt)stmt;
			CPPLabeledStatement cppstmt=new CPPLabeledStatement(method);
			cppstmt.setLabel(bs.getLabel());
			cppstmt.setStatement(create(strategies,method,bs.getStmt()));
			return cppstmt;
			
		}else if (stmt instanceof ReturnStmt){
			ReturnStmt bs=(ReturnStmt)stmt;
			CPPReturnStatement cppstmt=new CPPReturnStatement(method);
			cppstmt.setExpression(create(strategies,method,bs.getExpr()));
			return cppstmt;
			
		}else if (stmt instanceof SwitchEntryStmt){
			SwitchEntryStmt bs=(SwitchEntryStmt)stmt;
			CPPSwitchEntryStatement cppstmt=new CPPSwitchEntryStatement(method);
			cppstmt.setLabel(create(strategies,method,bs.getLabel()));
			if (bs.getStmts()!=null){
				for (Statement s : bs.getStmts()){
					cppstmt.addStatement(create(strategies,method,s));
				}
			}
			return cppstmt;
			
		}else if (stmt instanceof SwitchStmt){
			SwitchStmt bs=(SwitchStmt)stmt;
			CPPSwitchStatement cppstmt=new CPPSwitchStatement(method);
			cppstmt.setSelector(create(strategies,method,bs.getSelector()));
			for (SwitchEntryStmt s : bs.getEntries()){
				cppstmt.addEntry((CPPSwitchEntryStatement)create(strategies,method,s));
			}
			return cppstmt;
			
		}else if (stmt instanceof SynchronizedStmt){
			SynchronizedStmt bs=(SynchronizedStmt)stmt;
			CPPSynchronizedStatement cppstmt=new CPPSynchronizedStatement(method);
			cppstmt.setBlockStatement((CPPBlockStatement)create(strategies,method,bs.getBlock()));
			cppstmt.setExpression(create(strategies,method,bs.getExpr()));
			return cppstmt;
			
		}else if (stmt instanceof ThrowStmt){
			ThrowStmt bs=(ThrowStmt)stmt;
			CPPThrowStatement cppstmt=new CPPThrowStatement(method);
			cppstmt.setExpression(create(strategies,method,bs.getExpr()));
			return cppstmt;
			
		}else if (stmt instanceof TryStmt){
			TryStmt bs=(TryStmt)stmt;
			CPPTryStatement cppstmt=new CPPTryStatement(method);
			cppstmt.setFinallyBlock((CPPBlockStatement)create(strategies,method,bs.getFinallyBlock()));
			cppstmt.setTryBlock((CPPBlockStatement)create(strategies,method,bs.getTryBlock()));
			if (bs.getCatchs()!=null){
				for (CatchClause c : bs.getCatchs()){
					cppstmt.addCatch((CPPCatchClauseStatement)create(strategies,method,c));
				}
			}
			for (VariableDeclarationExpr e : bs.getResources()){
				cppstmt.addResource((CPPVariableDeclarationExpression)create(strategies,method,e));
			}
			return cppstmt;
			
		}else if (stmt instanceof TypeDeclarationStmt){
			TypeDeclarationStmt bs=(TypeDeclarationStmt)stmt;
			CPPTypeDeclarationStatement cppstmt=new CPPTypeDeclarationStatement(method);
			cppstmt.setTypeDeclaration((CPPTypeDeclaration)createBody(strategies,method,bs.getTypeDeclaration()));
			return cppstmt;
			
		}else if (stmt instanceof WhileStmt){
			WhileStmt bs=(WhileStmt)stmt;
			CPPWhileStatement cppstmt=new CPPWhileStatement(method);
			cppstmt.setBody(create(strategies,method,bs.getBody()));
			cppstmt.setCondition(create(strategies,method,bs.getCondition()));
			return cppstmt;
			
		}
		throw new RuntimeException("unknown statement type "+stmt+" class="+stmt.getClass());
	}

	public static CPPExpression create(IStrategies strategies,CPPMethod method,Expression expr){
		if (expr==null){
			return null;
		}
		if (expr instanceof ArrayAccessExpr){
			ArrayAccessExpr e=(ArrayAccessExpr)expr;
			CPPArrayAccessExpression cppExpr=new CPPArrayAccessExpression(method);
			cppExpr.setIndex(create(strategies,method,e.getIndex()));
			cppExpr.setName(create(strategies,method,e.getName()));
			return cppExpr;

		}else if (expr instanceof ArrayCreationExpr){
			ArrayCreationExpr e=(ArrayCreationExpr)expr;
			CPPArrayCreationExpression cppExpr=new CPPArrayCreationExpression(method);
			cppExpr.setArrayCount(e.getArrayCount());
			cppExpr.setInitializer((CPPArrayInitializerExpression)create(strategies,method,e.getInitializer()));
			cppExpr.setType(createType(strategies,method,e.getType()));
			if (e.getDimensions()!=null){
				for (Expression ee : e.getDimensions()){
					cppExpr.addDimension(create(strategies,method,ee));
				}
			}
			System.out.println("ArrayCreationExpr== "+e+" e.getArrayCount=="+e.getArrayCount());
			System.out.println("					      e.getInitializer=="+e.getInitializer());
			System.out.println("					      e.getType=="+e.getType());
			System.out.println("					      e.getDimensions=="+e.getDimensions());
			return cppExpr;

		}else if (expr instanceof ArrayInitializerExpr){
			ArrayInitializerExpr e=(ArrayInitializerExpr)expr;
			CPPArrayInitializerExpression cppExpr=new CPPArrayInitializerExpression(method);
			if (e.getValues()!=null){
				for (Expression ee : e.getValues()){
					cppExpr.addValue(create(strategies,method,ee));
				}
			}
			System.out.println("ArrayInitializerExpr== "+e+" value=="+e.getValues());
			return cppExpr;

		}else if (expr instanceof AssignExpr){
			AssignExpr e=(AssignExpr)expr;
			CPPAssignExpression cppExpr=new CPPAssignExpression(method);
			cppExpr.setTarget(create(strategies,method,e.getTarget()));
			cppExpr.setValue(create(strategies,method,e.getValue()));
			cppExpr.setOperator(create(strategies,method,e.getOperator()));
			return cppExpr;

		}else if (expr instanceof BinaryExpr){
			BinaryExpr e=(BinaryExpr)expr;
			CPPBinaryExpression cppExpr=new CPPBinaryExpression(method);
			cppExpr.setLeft(create(strategies,method,e.getLeft()));
			cppExpr.setRight(create(strategies,method,e.getRight()));
			cppExpr.setOperator(create(strategies,method,e.getOperator()));
			return cppExpr;

		}else if (expr instanceof BooleanLiteralExpr){
			BooleanLiteralExpr e=(BooleanLiteralExpr)expr;
			CPPBooleanLiteralExpression cppExpr=new CPPBooleanLiteralExpression(method);
			cppExpr.setValue(""+e.getValue());
			return cppExpr;

		}else if (expr instanceof CastExpr){
			CastExpr e=(CastExpr)expr;
			CPPCastExpression cppExpr=new CPPCastExpression(method);
			cppExpr.setExpression(create(strategies,method,e.getExpr()));
			cppExpr.setType(createType(strategies,method,e.getType()));
			return cppExpr;

		}else if (expr instanceof CharLiteralExpr){
			CharLiteralExpr e=(CharLiteralExpr)expr;
			CPPCharLiteralExpression cppExpr=new CPPCharLiteralExpression(method);
			cppExpr.setValue(e.getValue());
			return cppExpr;

		}else if (expr instanceof ClassExpr){
			ClassExpr e=(ClassExpr)expr;
			CPPClassExpression cppExpr=new CPPClassExpression(method);
			cppExpr.setType(createType(strategies,method,e.getType()));
			return cppExpr;

		}else if (expr instanceof ConditionalExpr){
			ConditionalExpr e=(ConditionalExpr)expr;
			CPPConditionalExpression cppExpr=new CPPConditionalExpression(method);
			cppExpr.setCondition(create(strategies,method,e.getCondition()));
			cppExpr.setElseExpression(create(strategies,method,e.getElseExpr()));
			cppExpr.setThenExpression(create(strategies,method,e.getThenExpr()));
			return cppExpr;

		}else if (expr instanceof DoubleLiteralExpr){
			DoubleLiteralExpr e=(DoubleLiteralExpr)expr;
			CPPDoubleLiteralExpression cppExpr=new CPPDoubleLiteralExpression(method);
			cppExpr.setValue(e.getValue());
			return cppExpr;

		}else if (expr instanceof EnclosedExpr){
			EnclosedExpr e=(EnclosedExpr)expr;
			CPPEnclosedExpression cppExpr=new CPPEnclosedExpression(method);
			cppExpr.setInner(create(strategies,method,e.getInner()));
			return cppExpr;

		}else if (expr instanceof FieldAccessExpr){
			FieldAccessExpr e=(FieldAccessExpr)expr;
			CPPFieldAccessExpression cppExpr=new CPPFieldAccessExpression(method);
			cppExpr.setField(e.getField());
			cppExpr.setFieldExpression((CPPNameExpression)create(strategies,method,e.getFieldExpr()));
			cppExpr.setScope(create(strategies,method,e.getScope()));
			if (e.getTypeArgs()!=null){
				for (Type t : e.getTypeArgs()){
					cppExpr.addTypeArg(createType(strategies,method,t));
				}
			}
			return cppExpr;

		}else if (expr instanceof InstanceOfExpr){
			InstanceOfExpr e=(InstanceOfExpr)expr;
			CPPInstanceOfExpression cppExpr=new CPPInstanceOfExpression(method);
			cppExpr.setExpression(create(strategies,method,e.getExpr()));
			cppExpr.setType(createType(strategies,method,e.getType()));
			return cppExpr;

		}else if (expr instanceof IntegerLiteralExpr){
			IntegerLiteralExpr e=(IntegerLiteralExpr)expr;
			CPPIntegerLiteralExpression cppExpr=new CPPIntegerLiteralExpression(method);
			cppExpr.setValue(e.getValue());
			return cppExpr;

		}else if (expr instanceof LongLiteralExpr){
			LongLiteralExpr e=(LongLiteralExpr)expr;
			CPPLongLiteralExpression cppExpr=new CPPLongLiteralExpression(method);
			cppExpr.setValue(e.getValue());
			return cppExpr;

		}else if (expr instanceof MethodCallExpr){
			MethodCallExpr e=(MethodCallExpr)expr;
			CPPMethodCallExpression cppExpr=new CPPMethodCallExpression(method);
			cppExpr.setName(e.getName());
			cppExpr.setNameExpression((CPPNameExpression)create(strategies,method,e.getNameExpr()));
			cppExpr.setScope(create(strategies,method,e.getScope()));
			if (e.getArgs()!=null){
				for (Expression ee : e.getArgs()){
					cppExpr.addArg(create(strategies,method,ee));
				}
			}
			if (e.getTypeArgs()!=null){
				for (Type t : e.getTypeArgs()){
					cppExpr.addTypeArg(createType(strategies,method,t));
				}
			}
			return cppExpr;

		}else if (expr instanceof NameExpr){
			NameExpr e=(NameExpr)expr;
			CPPNameExpression cppExpr=new CPPNameExpression(method);
			cppExpr.setName(e.getName());
			return cppExpr;

		}else if (expr instanceof NullLiteralExpr){
			NullLiteralExpr e=(NullLiteralExpr)expr;
			CPPNullLiteralExpression cppExpr=new CPPNullLiteralExpression(method);
			return cppExpr;

		}else if (expr instanceof ObjectCreationExpr){
			ObjectCreationExpr e=(ObjectCreationExpr)expr;
			CPPObjectCreationExpression cppExpr=new CPPObjectCreationExpression(method);
			cppExpr.setType(createType(strategies,method,e.getType()));
			cppExpr.setScope(create(strategies,method,e.getScope()));
			if (e.getArgs()!=null){
				for (Expression ee : e.getArgs()){
					cppExpr.addArg(create(strategies,method,ee));
				}
			}
			if (e.getTypeArgs()!=null){
				for (Type t : e.getTypeArgs()){
					cppExpr.addTypeArg(createType(strategies,method,t));
				}
			}
			if (e.getAnonymousClassBody()!=null){
				for (BodyDeclaration b : e.getAnonymousClassBody()){
					cppExpr.addAnonymousClassBody(createBody(strategies,method,b));
				}
			}
			return cppExpr;

		}else if (expr instanceof QualifiedNameExpr){
			QualifiedNameExpr e=(QualifiedNameExpr)expr;
			CPPQualifiedNameExpression cppExpr=new CPPQualifiedNameExpression(method);
			cppExpr.setName(e.getName());
			cppExpr.setQualifier((CPPNameExpression)create(strategies,method,e.getQualifier()));
			return cppExpr;

		}else if (expr instanceof StringLiteralExpr){
			StringLiteralExpr e=(StringLiteralExpr)expr;
			CPPStringLiteralExpression cppExpr=new CPPStringLiteralExpression(method);
			cppExpr.setValue(e.getValue());
			return cppExpr;

		}else if (expr instanceof SuperExpr){
			SuperExpr e=(SuperExpr)expr;
			CPPSuperExpression cppExpr=new CPPSuperExpression(method);
			cppExpr.setClassExpression(create(strategies,method,e.getClassExpr()));
			return cppExpr;

		}else if (expr instanceof ThisExpr){
			ThisExpr e=(ThisExpr)expr;
			CPPThisExpression cppExpr=new CPPThisExpression(method);
			cppExpr.setClassExpression(create(strategies,method,e.getClassExpr()));
			return cppExpr;

		}else if (expr instanceof UnaryExpr){
			UnaryExpr e=(UnaryExpr)expr;
			CPPUnaryExpression cppExpr=new CPPUnaryExpression(method);
			cppExpr.setExpression(create(strategies,method,e.getExpr()));
			cppExpr.setOperator(create(strategies,method,e.getOperator()));
			return cppExpr;

		}else if (expr instanceof VariableDeclarationExpr){
			VariableDeclarationExpr e=(VariableDeclarationExpr)expr;
			CPPVariableDeclarationExpression cppExpr=new CPPVariableDeclarationExpression(method);
			cppExpr.setModifiers(e.getModifiers());
			cppExpr.setType(createType(strategies,method,(Type)e.getType()));
			if (e.getVars()!=null){
				for (VariableDeclarator v : e.getVars()){
					cppExpr.addVar(createDeclarator(strategies,method,v));
				}
			}
			return cppExpr;

		}
		throw new RuntimeException("unknown epxression string=="+expr+" class="+expr.getClass());
	}

	public static CPPMultiTypeParameter create(IStrategies strategies,CPPMethod method,MultiTypeParameter par){
		CPPMultiTypeParameter tp=new CPPMultiTypeParameter();
		if (par.getTypes()!=null){
			for (Type t : par.getTypes()){
				tp.addType(createType(strategies,method,t));
			}
		}
		return tp;
	}

	public static CPPParameter create(IStrategies strategies,CPPMethod method,Parameter p){
		CPPParameter tp=new CPPParameter();
		tp.setType(createType(strategies,method,p.getType()));
		tp.setIsVarArgs(p.isVarArgs());
		tp.setModifiers(p.getModifiers());

		CPPVariableDeclaratorId id=new CPPVariableDeclaratorId();
		id.setArrayCount(p.getId().getArrayCount());
		id.setName(p.getId().getName());
		tp.setId(id);
		return tp;
	}

	public static CPPBodyDeclaration createBody(IStrategies strategies,CPPMethod method,BodyDeclaration b){
		if (b instanceof TypeDeclaration){
			TypeDeclaration td=(TypeDeclaration)b;
			CPPTypeDeclaration cpptd=new CPPTypeDeclaration();
			if (td.getMembers()!=null){
				for (BodyDeclaration b1 : td.getMembers()){
					cpptd.addMember(createBody(strategies,method,b1));
				}
			}
			cpptd.setName(td.getName());
			cpptd.setModifiers(td.getModifiers());
			cpptd.setNameExpression((CPPNameExpression)create(strategies,method,td.getNameExpr()));
			return cpptd;
		
		}else if (b instanceof MethodDeclaration){
			MethodDeclaration td=(MethodDeclaration)b;
			CPPMethodDeclaration cpptd=new CPPMethodDeclaration();
			cpptd.setArrayCount(td.getArrayCount());
			cpptd.setModifiers(td.getModifiers());
			cpptd.setName(td.getName());
			cpptd.setBody((CPPBlockStatement)create(strategies,method,td.getBody()));
			cpptd.setNameExpression((CPPNameExpression)create(strategies,method,td.getNameExpr()));
			if (td.getParameters()!=null){
				for (Parameter p : td.getParameters()){
					cpptd.addParameter(create(strategies,method,p));
				}
			}
			cpptd.setType(createType(strategies,method,td.getType()));
			return cpptd;
		}
		throw new RuntimeException("unknown body declaration body=="+b+" class="+b.getClass());
		//return null;
	}

	public static CPPVariableDeclarator createDeclarator(IStrategies strategies,CPPMethod method,VariableDeclarator v){
		CPPVariableDeclarator cppVariableDeclarator=new CPPVariableDeclarator();

		CPPVariableDeclaratorId id=new CPPVariableDeclaratorId();
		id.setArrayCount(v.getId().getArrayCount());
		id.setName(v.getId().getName());

		cppVariableDeclarator.setId(id);

		CPPExpression init=create(strategies,method,v.getInit());
		cppVariableDeclarator.setInit(init);
		return cppVariableDeclarator;
	}

	public static CPPType createType(IStrategies strategies,CPPMethod method,Type t){
		CPPType cppType=null;
		if (t instanceof PrimitiveType){
			PrimitiveType pt=(PrimitiveType)t;
			if (PrimitiveType.Primitive.Boolean.equals(pt.getType())){
				return CPPType.BOOLEAN_TYPE;

			}else if (PrimitiveType.Primitive.Byte.equals(pt.getType())){
				return CPPType.BYTE_TYPE;

			}else if (PrimitiveType.Primitive.Char.equals(pt.getType())){
				return CPPType.CHAR_TYPE;

			}else if (PrimitiveType.Primitive.Double.equals(pt.getType())){
				return CPPType.DOUBLE_TYPE;

			}else if (PrimitiveType.Primitive.Float.equals(pt.getType())){
				return CPPType.FLOAT_TYPE;

			}else if (PrimitiveType.Primitive.Int.equals(pt.getType())){
				return CPPType.INT_TYPE;

			}else if (PrimitiveType.Primitive.Long.equals(pt.getType())){
				return CPPType.LONG_TYPE;

			}else if (PrimitiveType.Primitive.Short.equals(pt.getType())){
				return CPPType.SHORT_TYPE;
			} 
 
		}else if (t instanceof VoidType){
			return CPPType.VOID_TYPE;

		}else if (t instanceof ClassOrInterfaceType){
			ClassOrInterfaceType ci=(ClassOrInterfaceType)t;
			cppType=strategies.getClassBuilderStrategy().getCPPType(ci.getName());
			cppType=method.getClazz().getSource().fixType(cppType);
		
		}else if (t instanceof ReferenceType){
			ReferenceType rt=(ReferenceType)t;
			if (rt.getType() instanceof PrimitiveType){
				PrimitiveType etype=(PrimitiveType)rt.getType();

				if (PrimitiveType.Primitive.Boolean.equals(etype.getType())){
					return CPPType.BOOLEAN_ARRAY_TYPE;

				}else if (PrimitiveType.Primitive.Byte.equals(etype.getType())){
					return CPPType.BYTE_ARRAY_TYPE;

				}else if (PrimitiveType.Primitive.Char.equals(etype.getType())){
					return CPPType.CHAR_ARRAY_TYPE;

				}else if (PrimitiveType.Primitive.Double.equals(etype.getType())){
					return CPPType.DOUBLE_ARRAY_TYPE;

				}else if (PrimitiveType.Primitive.Float.equals(etype.getType())){
					return CPPType.FLOAT_ARRAY_TYPE;

				}else if (PrimitiveType.Primitive.Int.equals(etype.getType())){
					return CPPType.INT_ARRAY_TYPE;

				}else if (PrimitiveType.Primitive.Long.equals(etype.getType())){
					return CPPType.LONG_ARRAY_TYPE;

				}else if (PrimitiveType.Primitive.Short.equals(etype.getType())){
					return CPPType.SHORT_ARRAY_TYPE;
				}
			}
			CPPType elementType=createType(strategies,method,rt.getType());
			if (rt.getArrayCount()>0){
				cppType=CPPType.getArrayType(elementType);
			}else{
				cppType=elementType;
			}
		}
		if (cppType==null){
			throw new RuntimeException("unknown type "+t);
		}
		method.getClazz().getSource().addDependency(cppType);
		return cppType;
	}

	public static CPPAssignExpression.Operator create(IStrategies strategies,CPPMethod method,AssignExpr.Operator o){
		if (o.equals(AssignExpr.Operator.and)){
			return CPPAssignExpression.Operator.and;
		
		} else if (o.equals(AssignExpr.Operator.assign)){
			return CPPAssignExpression.Operator.assign;
		
		}else if (o.equals(AssignExpr.Operator.lShift)){
			return CPPAssignExpression.Operator.lShift;
		
		}else if (o.equals(AssignExpr.Operator.minus)){
			return CPPAssignExpression.Operator.minus;
		
		}else if (o.equals(AssignExpr.Operator.or)){
			return CPPAssignExpression.Operator.or;
		
		}else if (o.equals(AssignExpr.Operator.plus)){
			return CPPAssignExpression.Operator.plus;
		
		}else if (o.equals(AssignExpr.Operator.rem)){
			return CPPAssignExpression.Operator.rem;
		
		}else if (o.equals(AssignExpr.Operator.rSignedShift)){
			return CPPAssignExpression.Operator.rSignedShift;
		
		}else if (o.equals(AssignExpr.Operator.rUnsignedShift)){
			return CPPAssignExpression.Operator.rUnsignedShift;
		
		}else if (o.equals(AssignExpr.Operator.slash)){
			return CPPAssignExpression.Operator.slash;
		
		}else if (o.equals(AssignExpr.Operator.star)){
			return CPPAssignExpression.Operator.star;
		
		}else if (o.equals(AssignExpr.Operator.xor)){
			return CPPAssignExpression.Operator.xor;
		}
		throw new RuntimeException("unknown operator type "+o);
	}

	public static CPPBinaryExpression.Operator create(IStrategies strategies,CPPMethod method,BinaryExpr.Operator o){
		if (o.equals(BinaryExpr.Operator.and)){
			return CPPBinaryExpression.Operator.and;
		
		} else if (o.equals(BinaryExpr.Operator.binAnd)){
			return CPPBinaryExpression.Operator.binAnd;
		
		}else if (o.equals(BinaryExpr.Operator.binOr)){
			return CPPBinaryExpression.Operator.binOr;
		
		}else if (o.equals(BinaryExpr.Operator.divide)){
			return CPPBinaryExpression.Operator.divide;
		
		}else if (o.equals(BinaryExpr.Operator.equals)){
			return CPPBinaryExpression.Operator.equals;
		
		}else if (o.equals(BinaryExpr.Operator.greater)){
			return CPPBinaryExpression.Operator.greater;
		
		}else if (o.equals(BinaryExpr.Operator.greaterEquals)){
			return CPPBinaryExpression.Operator.greaterEquals;
		
		}else if (o.equals(BinaryExpr.Operator.less)){
			return CPPBinaryExpression.Operator.less;
		
		}else if (o.equals(BinaryExpr.Operator.lessEquals)){
			return CPPBinaryExpression.Operator.lessEquals;
		
		}else if (o.equals(BinaryExpr.Operator.lShift)){
			return CPPBinaryExpression.Operator.lShift;
		
		}else if (o.equals(BinaryExpr.Operator.minus)){
			return CPPBinaryExpression.Operator.minus;
		
		}else if (o.equals(BinaryExpr.Operator.notEquals)){
			return CPPBinaryExpression.Operator.notEquals;
		
		}else if (o.equals(BinaryExpr.Operator.or)){
			return CPPBinaryExpression.Operator.or;
		
		}else if (o.equals(BinaryExpr.Operator.plus)){
			return CPPBinaryExpression.Operator.plus;
		
		}else if (o.equals(BinaryExpr.Operator.remainder)){
			return CPPBinaryExpression.Operator.remainder;
		
		}else if (o.equals(BinaryExpr.Operator.rSignedShift)){
			return CPPBinaryExpression.Operator.rSignedShift;
		
		}else if (o.equals(BinaryExpr.Operator.rUnsignedShift)){
			return CPPBinaryExpression.Operator.rUnsignedShift;
		
		}else if (o.equals(BinaryExpr.Operator.times)){
			return CPPBinaryExpression.Operator.times;
		
		}else if (o.equals(BinaryExpr.Operator.xor)){
			return CPPBinaryExpression.Operator.xor;
		
		}
		throw new RuntimeException("unknown operator type "+o);
	}

	public static CPPUnaryExpression.Operator create(IStrategies strategies,CPPMethod method,UnaryExpr.Operator o){
		if (o.equals(UnaryExpr.Operator.inverse)){
			return CPPUnaryExpression.Operator.inverse;

		}else if (o.equals(UnaryExpr.Operator.negative)){
			return CPPUnaryExpression.Operator.negative;

		}else if (o.equals(UnaryExpr.Operator.not)){
			return CPPUnaryExpression.Operator.not;

		}else if (o.equals(UnaryExpr.Operator.posDecrement)){
			return CPPUnaryExpression.Operator.posDecrement;

		}else if (o.equals(UnaryExpr.Operator.posIncrement)){
			return CPPUnaryExpression.Operator.posIncrement;

		}else if (o.equals(UnaryExpr.Operator.positive)){
			return CPPUnaryExpression.Operator.positive;

		}else if (o.equals(UnaryExpr.Operator.preDecrement)){
			return CPPUnaryExpression.Operator.preDecrement;

		}else if (o.equals(UnaryExpr.Operator.preIncrement)){
			return CPPUnaryExpression.Operator.preIncrement;

		}
		throw new RuntimeException("unknown operator type "+o);
	}
}
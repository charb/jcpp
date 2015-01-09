package jcpp.converter.builder;

import jcpp.converter.model.*;
import jcpp.converter.model.stmt.*;
import jcpp.converter.strategies.*;
import java.io.*;
import java.util.*;
import org.objectweb.asm.*;
import japa.parser.*;
import japa.parser.ast.*;
import japa.parser.ast.stmt.*;
import japa.parser.ast.body.*;
import japa.parser.ast.visitor.*;

public class CPPClassBuilder{
	protected IStrategies strategies;

	public CPPClassBuilder(IStrategies strategies){
		this.strategies=strategies;
	}

	public CPPClass build(CPPPackage pckge, File byteFile, File sourceFile) throws Exception{
		try{
			CPPClass clazz=new CPPClass(pckge);
			String n=sourceFile.getName();
			int index=n.lastIndexOf(".");
			if (index>0){
				n=n.substring(0,index);
			}
			clazz.setJavaClassName(n);

			ClassReader cr=new ClassReader(new FileInputStream(byteFile));
			buildFromByteCode(pckge,clazz,cr);

			if (!clazz.isInterface()){
				CompilationUnit	cu=JavaParser.parse(sourceFile);
				List<MethodDeclaration> methodDeclarations=new ArrayList<MethodDeclaration>();
				List<ConstructorDeclaration> constructorDeclarations=new ArrayList<ConstructorDeclaration>();
				cu.accept((VoidVisitor)new MethodSourceVisitor(clazz,methodDeclarations,constructorDeclarations),null);
				buildCPPMethodFromMethod(clazz,methodDeclarations);
				buildCPPMethodFromConstructor(clazz,constructorDeclarations);
			}

			clazz.setDependencies();
			return clazz;
		}catch(Throwable th){
			throw new Exception("Error while parsing file byteFile="+byteFile+" sourceFile=="+sourceFile,th);
		}
	}

	protected class MethodSourceVisitor extends VoidVisitorAdapter<Object>{
		protected CPPClass clazz;
		private List<MethodDeclaration> methodDeclarations;
		private List<ConstructorDeclaration> constructorDeclarations;

		public MethodSourceVisitor(CPPClass clazz,List<MethodDeclaration> methodDeclarations,List<ConstructorDeclaration> constructorDeclarations){
			this.clazz=clazz;
			this.methodDeclarations=methodDeclarations;
			this.constructorDeclarations=constructorDeclarations;
		}

		public void visit(final ClassOrInterfaceDeclaration n, final Object arg) {
			if (n.getName().equals(clazz.getJavaClassName())){
				super.visit(n,arg);
			}
			//skip internal classes
		}

		public void visit(MethodDeclaration n, Object arg){
			methodDeclarations.add(n);
		}

		public void visit(ConstructorDeclaration n, Object arg){
			constructorDeclarations.add(n);
		}
	}

	protected void buildCPPMethodFromConstructor(CPPClass clazz,List<ConstructorDeclaration> constructorDeclarations){
		for (ConstructorDeclaration cd : constructorDeclarations){
			if (!ModifierSet.isAbstract(cd.getModifiers())) {
				CPPMethod method=clazz.getSource().getMethod(cd.getBeginLine(),cd.getEndLine());
				if (method!=null){
					setParameterNames(method,cd);
					BlockStmt blockStmt=cd.getBlock();
					method.setBody((CPPBlockStatement)CPPModelFactory.create(strategies,method,blockStmt));
				}else{
					throw new RuntimeException("Cannot find constructor "+cd+" at begin line "+cd.getBeginLine()+" and at end line "+cd.getEndLine()+" in class "+clazz.getJavaClassName());
				}
			}
		}
	}

	protected void buildCPPMethodFromMethod(CPPClass clazz,List<MethodDeclaration> methodDeclarations){
		for (MethodDeclaration md : methodDeclarations){
			if (!ModifierSet.isAbstract(md.getModifiers())) {
				CPPMethod method=clazz.getSource().getMethod(md.getBeginLine(),md.getEndLine());
				if (method!=null){
					setParameterNames(method,md);
					BlockStmt blockStmt=md.getBody();
					method.setBody((CPPBlockStatement)CPPModelFactory.create(strategies,method,blockStmt));
				}else{
					throw new RuntimeException("Cannot find method "+md+" at begin line "+md.getBeginLine()+" and at end line "+md.getEndLine()+" in class "+clazz.getJavaClassName());
				}
			}
		}
	}

	protected void setParameterNames(CPPMethod method, MethodDeclaration md){
		if (md.getParameters()!=null){
			for (Parameter p : md.getParameters()){
				method.getInfo().addParameterName(p.getId().getName());
			}
		}
	}

	protected void setParameterNames(CPPMethod method, ConstructorDeclaration cd){
		if (cd.getParameters()!=null){
			for (Parameter p : cd.getParameters()){
				method.getInfo().addParameterName(p.getId().getName());
			}
		}
	}

	protected class CPPMethodNode implements MethodVisitor{
		protected CPPMethod method;
		protected boolean first;

		public CPPMethodNode(CPPMethod method){
			this.method=method;
			first=true;
		}

		public AnnotationVisitor visitAnnotationDefault(){
			return null;
		}

	  	public AnnotationVisitor visitAnnotation(String paramString, boolean paramBoolean){
			return null;
		}

	  	public AnnotationVisitor visitParameterAnnotation(int paramInt, String paramString, boolean paramBoolean){
			return null;
		}

	  	public void visitAttribute(Attribute paramAttribute){
		}

	  	public void visitCode(){
		}

	  	public void visitFrame(int type, int nLocal, Object[] local, int nStack, Object[] stack){
		}

	  	public void visitInsn(int opcode){
		}

	  	public void visitIntInsn(int opcode, int operand){
		}

	  	public void visitVarInsn(int opcode, int var){
		}

	  	public void visitTypeInsn(int opcode, String type){
	  		method.getClazz().getSource().addDependency(strategies.getClassBuilderStrategy().getCPPType(type));
		}

	  	public void visitFieldInsn(int opcode, String owner, String name, String desc){
	  		method.getClazz().getSource().addDependency(strategies.getClassBuilderStrategy().getCPPType(owner));
		}

	  	public void visitMethodInsn(int opcode, String owner, String name, String desc){
	  		method.getClazz().getSource().addDependency(strategies.getClassBuilderStrategy().getCPPType(owner));
		}

	  	public void visitJumpInsn(int opcode, Label label){
		}

	  	public void visitLabel(Label label){
		}

	  	public void visitLdcInsn(Object cst){
		}

	  	public void visitIincInsn(int var, int increment){
		}

	  	public void visitTableSwitchInsn(int min, int max, Label dflt, Label[] labels){
		}

	  	public void visitLookupSwitchInsn(Label dflt, int[] keys, Label[] labels){
		}

	  	public void visitMultiANewArrayInsn(String desc, int dims){
		}

	  	public void visitTryCatchBlock(Label start, Label end, Label handler, String type){
	  		method.getClazz().getSource().addDependency(strategies.getClassBuilderStrategy().getCPPType(type));
		}

	  	public void visitLocalVariable(String name, String desc, String signature, Label start, Label end, int index){
		}

	  	public void visitLineNumber(int line, Label start){
	  		if (first){
	  			method.getInfo().setLineNumber(line);
	  			first=false;
	  		}
		}

	  	public void visitMaxs(int maxStack, int maxLocals){
		}

	  	public void visitEnd(){
			method.getClazz().getHeader().addMethod(method.getInfo());
	  		method.getClazz().getSource().addMethod(method);
		}
	}

	protected void buildFromByteCode(final CPPPackage pckge, final CPPClass clazz, ClassReader reader) throws Exception{
	 	ClassVisitor cv=new ClassVisitor(){

			public FieldVisitor visitField(int access, String name, String desc, String signature, Object value){
				CPPType cppType=strategies.getClassBuilderStrategy().getCPPType(Type.getType(desc));
				CPPField field=new CPPField(clazz);
				if ((access & Opcodes.ACC_STATIC) >0){
					field.setStatic(true);
				}
				if ((access & Opcodes.ACC_PROTECTED) >0 || (access & Opcodes.ACC_PRIVATE)>0) {
					field.setProtected(true);
				}
				field.setType(cppType);
				field.setName(name);
				//TODO array+init expr
				clazz.addField(field);				
				return null;
			}

			public MethodVisitor visitMethod(int access, String name, String desc, String signature, String[] exceptions){
				if (name.equals("<clinit>")){
					return null;//TODO
				}
				CPPMethodInfo mi=new CPPMethodInfo(clazz);
				if (name.equals("<init>")){
					mi.setName(clazz.getName());
					mi.setConstructor(true);
				}else{
					mi.setName(name);
				}
				mi.setSignature(desc);
				if ((access & Opcodes.ACC_ABSTRACT) >0){
					mi.setAbstract(true);
				}
				if ((access & Opcodes.ACC_STATIC) >0){
					mi.setStatic(true);
				}
				if ((access & Opcodes.ACC_PROTECTED) >0 || (access & Opcodes.ACC_PRIVATE)>0) {
					mi.setProtected(true);
				}
				Type mtype=Type.getReturnType(desc);
				mi.setReturnType(strategies.getClassBuilderStrategy().getCPPType(mtype));

				Type[] ps=Type.getArgumentTypes(desc);
				if (ps!=null){
					for (Type t : ps){
						mi.addParameter(strategies.getClassBuilderStrategy().getCPPType(t));
					}
				}

				CPPMethod method=new CPPMethod(clazz);
				method.setInfo(mi);

				return new CPPMethodNode(method);
			}

			public void visit(int version, int access, String name,String signature, String superName, String[] interfaces) {
				clazz.setIsInterface((access & Opcodes.ACC_INTERFACE)>0);
				clazz.setSuperJavaClassName(superName);

				if (interfaces!=null){
					for (String i : interfaces){
						clazz.addInterfaceJavaClassName(i);
					}
				}
				strategies.getClassBuilderStrategy().initialize(clazz);
				pckge.addClass(clazz);
			}

			public void visitSource(String source, String debug) {
			}

			public void visitOuterClass(String owner, String name, String desc) {
			}

			public AnnotationVisitor visitAnnotation(String desc,boolean visible) {
				return null;
			}

			public void visitAttribute(Attribute attr) {
			}

			public void visitInnerClass(String name, String outerName,String innerName, int access) {
			}

			public void visitEnd(){
			}
		};
		reader.accept(cv,0);
	}
}
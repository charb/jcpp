package jcpp.model.cpp.ast;

import org.eclipse.cdt.core.dom.ast.*;
import jcpp.model.cpp.ast.location.*;
import jcpp.model.cpp.ast.declaration.*;
import jcpp.model.cpp.ast.macro.*;
import jcpp.model.cpp.ast.stmt.*;
import java.util.*;
import java.io.*;
import org.eclipse.cdt.core.dom.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import org.eclipse.cdt.core.dom.ast.c.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.gnu.cpp.*;
import org.eclipse.cdt.core.parser.*;
import org.eclipse.cdt.internal.core.dom.parser.*;
import org.eclipse.cdt.core.index.*;
import org.eclipse.cdt.internal.core.parser.*;
import org.eclipse.cdt.internal.core.parser.scanner.*;

public class Sample{
	private ASTTranslationUnitConfig config;

	public Sample(){
	}

	public ASTTranslationUnitConfig getConfig(){
		return config;
	}

	public void setConfig(ASTTranslationUnitConfig c){
		config=c;
	}

	private static class FileProvider extends InternalFileContentProvider{
    	@Override
    	public InternalFileContent getContentForInclusion(String path,IMacroDictionary macroDictionary) {
        	return (InternalFileContent) InternalFileContent.createForExternalFileLocation(path);
    	}

    	@Override
    	public InternalFileContent getContentForInclusion(IIndexFileLocation arg0, String arg1) {
        	return null;
    	}
	}

	public IASTTranslationUnit build() throws Exception{
		IParserLogService log = new IParserLogService(){
              public void traceLog(String paramString){
                    System.out.println(paramString);
              }

              public boolean isTracing(){
                    return true;
              }
        };		

        File file=new File(config.getFilePath());
        IScannerInfo info = new ScannerInfo(config.getMapSymbols(),config.getIncludesPath().toArray(new String[0]));
        FileContent ct = FileContent.createForExternalFileLocation(file.getAbsolutePath());

        IASTTranslationUnit translationUnit =GPPLanguage.getDefault().getASTTranslationUnit(ct, info, new FileProvider(),null, 0,log);
        return translationUnit;
    }

	private static void fillFiles(File f,List<File> files){
   		if (f.isDirectory()){
        	for (File f1 : f.listFiles()){
            	fillFiles(f1,files);
        	}
    	}else{
        	files.add(f);
    	}
  	}

    public static boolean isPointer(IASTDeclarator dec){
        IASTPointerOperator[] op=dec.getPointerOperators();
        if (op!=null){
            for (IASTPointerOperator o : op){
                return true;
            }
        }
        return false;
    }

    public static String getScopeName(IScope scope) throws Exception{
        List<IScope> scopes=new ArrayList();
        String str="";
        IScope current=scope;
        while (current!=null){
            scopes.add(current);
            current=current.getParent();
        }
        for (int i=0;i<scopes.size();i++){
            if (scopes.get(scopes.size()-1-i).getScopeName()!=null){
                str+=""+scopes.get(scopes.size()-1-i).getScopeName();
                if (i<scopes.size()-1){
                    str+=".";
                }
            }
        }
        return str;
    }

    public static IASTCompositeTypeSpecifier getParentClass(IASTNode simple) throws Exception{
        IASTNode parent=simple;
        while (parent!=null){
            if (parent instanceof IASTCompositeTypeSpecifier){
                return (IASTCompositeTypeSpecifier)parent;
            }
            parent=parent.getParent();
        }
        return null;
    }

    public static ICPPASTNamespaceDefinition getParentNamespace(IASTNode simple) throws Exception{
        IASTNode parent=simple;
        while (parent!=null){
            if (parent instanceof ICPPASTNamespaceDefinition){
                return (ICPPASTNamespaceDefinition)parent;
            }
            parent=parent.getParent();
        }
        return null;
    }

    public static ICPPASTFunctionDefinition getFunctionDefinition(IASTNode simple) throws Exception{
        IASTNode parent=simple;
        while (parent!=null){
            if (parent instanceof ICPPASTFunctionDefinition){
                return (ICPPASTFunctionDefinition)parent;
            }
            parent=parent.getParent();
        }
        return null;
    }

    public static void printParent(IASTNode simple,IName name) throws Exception{
        IASTCompositeTypeSpecifier composite=getParentClass(simple);
        if (composite!=null){
            System.out.println("Parent =="+getScopeName(composite.getScope()));
        }else{
            String s="";
            if (name instanceof ICPPASTQualifiedName){
                ICPPASTQualifiedName qn=(ICPPASTQualifiedName)name;
                for (ICPPASTNameSpecifier ns : qn.getQualifier()){
                    s+=new String(ns.toCharArray())+".";
                }
                if (s.length()>1){
                    s=s.substring(0,s.length()-1);
                }
            }

            ICPPASTNamespaceDefinition namespace=getParentNamespace(simple);
            if (namespace==null){
                System.out.println("Parent name == "+s);
            }else{
                System.out.println("Parent =="+getScopeName(namespace.getScope())+"."+s);
            }
        }
    }

    public static void main(String[] argv) throws Exception{
        ASTTranslationUnitConfig config=ASTTranslationUnitConfig.readFrom(new FileInputStream(new File(argv[0])));
        String parentAbsolutePath=config.getFilePath();
        File parent=new File(parentAbsolutePath);
        List<File> files=new ArrayList<File>();
        fillFiles(parent,files);

        for (File f : files){
            final File f2=f;
            System.out.println("Parsing file "+f.getAbsolutePath());
            String child=f.getAbsolutePath().substring(parentAbsolutePath.length());
            Sample builder=new Sample();
    		builder.setConfig(config);
    		config.setFilePath(f.getAbsolutePath());
    		final IASTTranslationUnit unit=builder.build();

            ASTVisitor visitor = new ASTVisitor() {
                public int visit(IASTName name) {
                    return ASTVisitor.PROCESS_CONTINUE;
                }

                public int visit(IASTTranslationUnit tu){
                    return ASTVisitor.PROCESS_CONTINUE;
                }

                public int visit(IASTDeclaration dec){
                    try{
                        if (f2.equals(new File(dec.getContainingFilename()))) {
                            if (dec instanceof IASTSimpleDeclaration){
                                IASTSimpleDeclaration simple = (IASTSimpleDeclaration) dec;
                                IASTDeclSpecifier declSpecifier=simple.getDeclSpecifier();
                                for (IASTDeclarator declarator : simple.getDeclarators()){
                                    IBinding binding = declarator.getName().resolveBinding();
                                    if (binding instanceof IField){
                                        IField field=(IField)binding;
                                        System.out.println("simple.getParent=="+simple.getParent().getClass());
                                        printParent(simple,declarator.getName());
                                        System.out.println("declSpecifier.getRawSignature ="+declSpecifier.getRawSignature());
                                        System.out.println("simple.getRawSignature ="+simple.getRawSignature());
                                        String simpleContent=unit.getRawSignature();
                                        char[] simpleCharContent=simpleContent.toCharArray();
                                        System.out.println("Last simple char=="+simpleCharContent[simple.getFileLocation().getNodeOffset()+simple.getFileLocation().getNodeLength()-1]);
                                        ICompositeType compositeType=field.getCompositeTypeOwner();
                                        String content=unit.getRawSignature();
                                        char[] charContent=content.toCharArray();
                                        System.out.println("declarator.getRawSignature ="+declarator.getRawSignature());
                                        System.out.println("Last char=="+charContent[declarator.getFileLocation().getNodeOffset()+declarator.getFileLocation().getNodeLength()-1]);
                                        System.out.println("declarator.getFileLocation ="+declarator.getFileLocation());
                                        System.out.println("Decl specifier Owner ="+compositeType.getName());
                                        System.out.println("               Field ="+field.getName()+" isPointer="+isPointer(declarator));

                                    } else if (binding instanceof IVariable){
                                        IVariable var=(IVariable)binding;
                                        System.out.println("variabl declarator.getName="+declarator.getName());
                                        System.out.println("variabl declarator.getName.class="+declarator.getName().getClass());
                                        printParent(simple,declarator.getName());
                                        ICPPASTFunctionDefinition funcDef=getFunctionDefinition(simple);
                                        if (funcDef!=null){
                                            IASTFunctionDeclarator funcDeclarator=funcDef.getDeclarator();
                                            System.out.println("variabl in Func name=="+funcDeclarator.getName().getLastName());
                                        }else{
                                            System.out.println("error variabl in Func name not found !!!!");
                                        }
                                        System.out.println("variabl name="+var.getName());
                                        System.out.println("variabl detected declarator.getRawSignature ="+declarator.getRawSignature());
                                        System.out.println("variabl detected declSpecifier.getRawSignature ="+declSpecifier.getRawSignature());
                                        System.out.println("variabl detected  simple.getRawSignature ="+simple.getRawSignature());
                                        String simpleContent=unit.getRawSignature();
                                        char[] simpleCharContent=simpleContent.toCharArray();
                                        System.out.println("variabl detected Last simple char=="+simpleCharContent[simple.getFileLocation().getNodeOffset()+simple.getFileLocation().getNodeLength()-1]);
                                    }
                                }
                            }else if (dec instanceof ICPPASTFunctionDefinition){
                                ICPPASTFunctionDefinition func=(ICPPASTFunctionDefinition)dec;
                                IASTFunctionDeclarator funcDeclarator=func.getDeclarator();
                                ICPPASTFunctionDeclarator cppFuncDeclarator=(ICPPASTFunctionDeclarator)funcDeclarator;
                                ICPPASTParameterDeclaration[] params=cppFuncDeclarator.getParameters();
                                printParent(func,funcDeclarator.getName());
                                if (params==null || params.length==0){
                                    System.out.println("Func name=="+funcDeclarator.getName().getLastName());
                                    System.out.println("     no param!");
                                }else{
                                    System.out.println("Func name=="+funcDeclarator.getName().getLastName());
                                    int i=0;
                                    for (ICPPASTParameterDeclaration p : params){
                                        ICPPASTDeclarator pdecl=p.getDeclarator();
                                        System.out.println("    param name["+i+"]="+pdecl.getName());
                                        i++;
                                    }
                                }
                            }
                        }
                        return ASTVisitor.PROCESS_CONTINUE;
                    }catch(Exception e){
                        e.printStackTrace();
                        return ASTVisitor.PROCESS_CONTINUE;
                    }
                }

                public int visit(IASTInitializer init) {
                    return ASTVisitor.PROCESS_CONTINUE;
                }

                public int visit(IASTParameterDeclaration dec) {
                    return ASTVisitor.PROCESS_CONTINUE;
                }

                public int visit(IASTDeclarator dec) {
                    if (f2.equals(new File(dec.getContainingFilename()))) {
                        // if (dec instanceof ICPPASTDeclarator){
                        //     System.out.println("CPP Declarator.getContainingFilename="+dec.getContainingFilename());
                        //     System.out.println("CPP Declarator="+dec);
                        //     System.out.println("CPP Declarator="+dec.getClass());
                        //     System.out.println("CPP Declarator.getName()="+dec.getName());
                        //     System.out.println("CPP Declarator.getName().binding="+dec.getName().resolveBinding());
                        //     if (dec.getName().resolveBinding()!=null){
                        //         System.out.println("CPP Declarator.getName().binding.class="+dec.getName().resolveBinding().getClass());
                        //     }
                        //     if (dec instanceof IASTFieldDeclarator){
                        //         IASTFieldDeclarator fieldDeclarator=(IASTFieldDeclarator)dec;
                        //         IBinding binding = fieldDeclarator.getName().resolveBinding();
                        //         IField field=(IField)binding;
                        //         ICompositeType compositeType=field.getCompositeTypeOwner();
                        //         System.out.println("Owner ="+compositeType.getName());
                        //         System.out.println("    Field "+field.getName());
                        //     }
                        // }
                        // if (dec instanceof ICPPASTFunctionDeclarator){
                        //     ICPPASTFunctionDeclarator function=(ICPPASTFunctionDeclarator)dec;
                        //     System.out.println("Function "+function.getName());
                        //     IASTParameterDeclaration[] params = function.getParameters();
                        //     if (params!=null){
                        //         int i=0;
                        //         for (IASTParameterDeclaration param : params){
                        //             IASTDeclarator paramDeclarator = param.getDeclarator(); 
                        //             System.out.println("    Parameter["+i+"]="+paramDeclarator.getName());
                        //             i++;
                        //         }
                        //     }
                        // }
                    }
                    return ASTVisitor.PROCESS_CONTINUE;
                }

                public int visit(IASTDeclSpecifier dec) {
                    // if (f2.equals(new File(dec.getContainingFilename()))) {
                    //     if (dec instanceof IASTCompositeTypeSpecifier){
                    //         IASTCompositeTypeSpecifier composite = (IASTCompositeTypeSpecifier) dec;
                    //         for (IASTDeclaration decl : composite.getMembers()){
                    //             if (decl instanceof IASTSimpleDeclaration){
                    //                 IASTSimpleDeclaration simple = (IASTSimpleDeclaration) decl;
                    //                 IASTDeclSpecifier declSpecifier=simple.getDeclSpecifier();
                    //                 for (IASTDeclarator declarator : simple.getDeclarators()){
                    //                     IBinding binding = declarator.getName().resolveBinding();
                    //                     if (binding instanceof IField){
                    //                         System.out.println("declSpecifier.getRawSignature ="+declSpecifier.getRawSignature());
                    //                         System.out.println("simple.getRawSignature ="+simple.getRawSignature());
                    //                         String simpleContent=unit.getRawSignature();
                    //                         char[] simpleCharContent=simpleContent.toCharArray();
                    //                         System.out.println("Last simple char=="+simpleCharContent[simple.getFileLocation().getNodeOffset()+simple.getFileLocation().getNodeLength()-1]);
                    //                         IField field=(IField)binding;
                    //                         ICompositeType compositeType=field.getCompositeTypeOwner();
                    //                         String content=unit.getRawSignature();
                    //                         char[] charContent=content.toCharArray();
                    //                         System.out.println("declarator.getRawSignature ="+declarator.getRawSignature());
                    //                         System.out.println("Last char=="+charContent[declarator.getFileLocation().getNodeOffset()+declarator.getFileLocation().getNodeLength()-1]);
                    //                         System.out.println("declarator.getFileLocation ="+declarator.getFileLocation());
                    //                         System.out.println("Decl specifier Owner ="+compositeType.getName());
                    //                         System.out.println("               Field ="+field.getName()+" isPointer="+isPointer(declarator));
                    //                     }
                    //                 }
                    //             }
                    //         }
                    //     }
                    // }
                    return ASTVisitor.PROCESS_CONTINUE;
                }

                public int visit(IASTArrayModifier mod){
                    return ASTVisitor.PROCESS_CONTINUE;
                }

                public int visit(IASTPointerOperator ptr){
                    return ASTVisitor.PROCESS_CONTINUE;
                }

                public int visit(IASTAttribute att){
                    return ASTVisitor.PROCESS_CONTINUE;
                }

                public int visit(IASTToken tok){
                    return ASTVisitor.PROCESS_CONTINUE;
                }

                public int visit(IASTExpression exp) {
                    return ASTVisitor.PROCESS_CONTINUE;
                }

                public int visit(IASTStatement stat) {
                    return ASTVisitor.PROCESS_CONTINUE;
                }

                public int visit(IASTTypeId id) {
                    return ASTVisitor.PROCESS_CONTINUE;
                }

                public int visit(IASTEnumerationSpecifier.IASTEnumerator en) {
                    return ASTVisitor.PROCESS_CONTINUE;
                }

                public int visit(IASTProblem pb) {
                    return ASTVisitor.PROCESS_CONTINUE;
                }

                public int visit(ICPPASTCompositeTypeSpecifier.ICPPASTBaseSpecifier bas){
                    return ASTVisitor.PROCESS_CONTINUE;
                }

                public int visit(ICPPASTNamespaceDefinition def){
                    return ASTVisitor.PROCESS_CONTINUE;
                }

                public int visit(ICPPASTTemplateParameter temp){
                    return ASTVisitor.PROCESS_CONTINUE;
                }

                public int visit(ICPPASTCapture cap){
                    return ASTVisitor.PROCESS_CONTINUE;
                }

                public int visit(ICASTDesignator des){
                    return ASTVisitor.PROCESS_CONTINUE;
                }

                public int visit(IASTComment com){
                    return ASTVisitor.PROCESS_CONTINUE;
                }

                public int leave(IASTComment com){
                    return ASTVisitor.PROCESS_CONTINUE;
                }

                public int visit(ASTAmbiguousNode node){
                    return ASTVisitor.PROCESS_CONTINUE;
                }
            };
            visitor.shouldVisitDeclarations = true;
            visitor.shouldVisitParameterDeclarations =true;
            visitor.shouldVisitDeclarators = true;
            visitor.shouldVisitDeclSpecifiers = true;
            visitor.shouldVisitArrayModifiers = true;
            visitor.shouldVisitPointerOperators = true;
            visitor.shouldVisitAttributes = true;
            visitor.shouldVisitTokens = true;
            visitor.shouldVisitExpressions = true;
            visitor.shouldVisitStatements = true;
            visitor.shouldVisitTypeIds = true;
            visitor.shouldVisitEnumerators = true;
            //visitor.shouldVisitTranslationUnit = true;
            visitor.shouldVisitProblems = true;
            visitor.shouldVisitDesignators = true;
            visitor.shouldVisitBaseSpecifiers = true;
            visitor.shouldVisitNamespaces = true;
            visitor.shouldVisitTemplateParameters = true;
            visitor.shouldVisitCaptures = true;
            visitor.includeInactiveNodes = true;
            visitor.shouldVisitAmbiguousNodes = true;
            visitor.shouldVisitImplicitNames = true;
            visitor.shouldVisitImplicitNameAlternates =true;
            visitor.shouldVisitArrayModifiers=true;
            visitor.shouldVisitDesignators=true;
            visitor.shouldVisitInitializers=true;
            visitor.shouldVisitNames=true;
            visitor.shouldVisitVirtSpecifiers=true;

            unit.accept(visitor);
    	}
    }
}
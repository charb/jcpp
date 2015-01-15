package jcpp.parser.cpp;

import java.io.File;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Stack;

import jcpp.parser.cpp.update.Updater;
import jcpp.parser.cpp.update.UpdatesResult;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.eclipse.cdt.core.dom.ast.ASTVisitor;
import org.eclipse.cdt.core.dom.ast.IASTDeclSpecifier;
import org.eclipse.cdt.core.dom.ast.IASTDeclaration;
import org.eclipse.cdt.core.dom.ast.IASTDeclarator;
import org.eclipse.cdt.core.dom.ast.IASTFunctionDeclarator;
import org.eclipse.cdt.core.dom.ast.IASTName;
import org.eclipse.cdt.core.dom.ast.IASTNode;
import org.eclipse.cdt.core.dom.ast.IASTProblem;
import org.eclipse.cdt.core.dom.ast.IASTSimpleDeclaration;
import org.eclipse.cdt.core.dom.ast.IASTTranslationUnit;
import org.eclipse.cdt.core.dom.ast.IBinding;
import org.eclipse.cdt.core.dom.ast.IField;
import org.eclipse.cdt.core.dom.ast.IFunction;
import org.eclipse.cdt.core.dom.ast.IVariable;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPASTCompositeTypeSpecifier;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPASTElaboratedTypeSpecifier;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPASTFunctionDefinition;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPASTNameSpecifier;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPASTNamespaceDefinition;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPASTQualifiedName;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPFunction;
import org.eclipse.cdt.core.dom.ast.gnu.cpp.GPPLanguage;
import org.eclipse.cdt.core.index.IIndexFileLocation;
import org.eclipse.cdt.core.parser.FileContent;
import org.eclipse.cdt.core.parser.IParserLogService;
import org.eclipse.cdt.core.parser.IScannerInfo;
import org.eclipse.cdt.core.parser.IncludeFileContentProvider;
import org.eclipse.cdt.core.parser.ScannerInfo;
import org.eclipse.cdt.internal.core.indexer.StdoutLogService;
import org.eclipse.cdt.internal.core.parser.IMacroDictionary;
import org.eclipse.cdt.internal.core.parser.scanner.InternalFileContent;
import org.eclipse.cdt.internal.core.parser.scanner.InternalFileContentProvider;


public class CPPParser extends ASTVisitor {
    private static final Log log = LogFactory.getLog(CPPParser.class);

    private Map<String, CPPFile> cppfiles;

    private File file;
    private List<String> includes;
    private Map<String, String> symbols;
    private IASTTranslationUnit translationUnit;

    private Stack<ICPPASTNamespaceDefinition> namespaces;
    private Stack<ICPPASTCompositeTypeSpecifier> compositeTypeSpecifiers;
    private Stack<ICPPASTFunctionDefinition> functionsDefinitions;


    public CPPParser() {
        cppfiles = new HashMap<String, CPPFile>();

        namespaces = new Stack<ICPPASTNamespaceDefinition>();
        compositeTypeSpecifiers = new Stack<ICPPASTCompositeTypeSpecifier>();
        functionsDefinitions = new Stack<ICPPASTFunctionDefinition>();

        shouldVisitDeclarations = true;
        shouldVisitDeclSpecifiers = true;
        shouldVisitNamespaces = true;
        shouldVisitProblems = true;
    }


    public CPPFile[] getCPPFiles() {
        return cppfiles.values().toArray(new CPPFile[0]);
    }

    public void setIncludes(List<String> includes) {
        this.includes = includes;
    }

    public void setSymbols(Map<String, String> symbols) {
        this.symbols = symbols;
    }

    public IASTTranslationUnit parse(File file) throws Exception {
        this.file = file;

        namespaces.clear();
        compositeTypeSpecifiers.clear();
        functionsDefinitions.clear();

        FileContent fileContent = FileContent.createForExternalFileLocation(file.getAbsolutePath());
        IScannerInfo scannerInfo = new ScannerInfo(symbols, includes.toArray(new String[0]));
        IncludeFileContentProvider fileCreator = new FileProvider();
        IParserLogService log = new StdoutLogService();

        log.traceLog("Parsing File: " + file.getAbsolutePath());
        translationUnit = GPPLanguage.getDefault().getASTTranslationUnit(fileContent, scannerInfo, fileCreator, null, 0, log);
        translationUnit.accept(this);
        return translationUnit;
    }

    @Override
    public int visit(ICPPASTNamespaceDefinition namespaceDefinition) {
        if (file.equals(new File(namespaceDefinition.getContainingFilename()))) {
            getCPPFile().addNamepsace(new CPPNamespace(namespaceDefinition));
            namespaces.push(namespaceDefinition);
        } else {
            if (log.isDebugEnabled()) {
                log.debug("Skipped namespace definition " + namespaceDefinition.getName() + " in file " + namespaceDefinition.getContainingFilename() + " (current file: " + file.getAbsolutePath() + ")");
            }
        }
        return ASTVisitor.PROCESS_CONTINUE;
    }

    @Override
    public int leave(ICPPASTNamespaceDefinition namespaceDefinition) {
        if (file.equals(new File(namespaceDefinition.getContainingFilename()))) {
            ICPPASTNamespaceDefinition current = namespaces.pop();
            if (namespaceDefinition != current) {
                throw new RuntimeException("Error while leaving namespace " + namespaceDefinition.getName() + " wherase namespace " + current + " is expected.");
            }
        }
        return ASTVisitor.PROCESS_CONTINUE;
    }

    @Override
    public int visit(IASTDeclSpecifier declSpec) {
        if (file.equals(new File(declSpec.getContainingFilename()))) {
            if (declSpec instanceof ICPPASTCompositeTypeSpecifier) {
                ICPPASTCompositeTypeSpecifier compositeTypeSpecifier = (ICPPASTCompositeTypeSpecifier) declSpec;
                compositeTypeSpecifiers.push(compositeTypeSpecifier);
                getCPPClass(compositeTypeSpecifier); //will create the CPPClass object if it doesn't exist.
            } else if (declSpec instanceof ICPPASTElaboratedTypeSpecifier) {
                ICPPASTElaboratedTypeSpecifier elaboratedTypeSpecifier = (ICPPASTElaboratedTypeSpecifier) declSpec;
                if ((elaboratedTypeSpecifier.getKind() == ICPPASTElaboratedTypeSpecifier.k_class) && !elaboratedTypeSpecifier.isFriend()) {
                    CPPFile cppFile = getCPPFile();
                    CPPClassForwardDeclaration classForwardDeclaration = new CPPClassForwardDeclaration(elaboratedTypeSpecifier, cppFile.getNamespace(getFullNamespace()));
                    cppFile.addClassForwardDeclaration(classForwardDeclaration);
                }
            } else {
                if (log.isDebugEnabled()) {
                    log.debug("Skipped non-class declaration specifier " + declSpec + " in file " + declSpec.getContainingFilename());
                }
            }
        } else {
            if (log.isDebugEnabled()) {
                log.debug("Skipped declaration specifier " + declSpec + " in file " + declSpec.getContainingFilename() + " (current file: " + file.getAbsolutePath() + ")");
            }
        }
        return ASTVisitor.PROCESS_CONTINUE;
    }

    @Override
    public int leave(IASTDeclSpecifier declSpec) {
        if (file.equals(new File(declSpec.getContainingFilename()))) {
            if (declSpec instanceof ICPPASTCompositeTypeSpecifier) {
                ICPPASTCompositeTypeSpecifier current = compositeTypeSpecifiers.pop();
                if (declSpec != current) {
                    throw new RuntimeException("Error while leaving class " + ((ICPPASTCompositeTypeSpecifier) declSpec).getName() + " wherase class " + current.getName() + " is expected.");
                }
            }
        }
        return ASTVisitor.PROCESS_CONTINUE;
    }

    @Override
    public int visit(IASTDeclaration declaration) {
        try {
            if (file.equals(new File(declaration.getContainingFilename()))) {
                if (declaration instanceof IASTSimpleDeclaration) {
                    IASTSimpleDeclaration simpleDeclaration = (IASTSimpleDeclaration) declaration;
                    for (IASTDeclarator declarator : simpleDeclaration.getDeclarators()) {
                        IBinding binding = declarator.getName().resolveBinding();
                        if (binding instanceof IField) {
                            // casting to the concrete class CPPField because the method getPrimaryDeclaration is not part of the IField interface
                            org.eclipse.cdt.internal.core.dom.parser.cpp.CPPField field = (org.eclipse.cdt.internal.core.dom.parser.cpp.CPPField) binding;
                            if (field.getPrimaryDeclaration() == simpleDeclaration) { //if "simpleDeclaration" is not the primary declaration then skip it.
                                CPPClass cppClass = getCPPClass(declarator.getName());
                                cppClass.addField(new CPPField(simpleDeclaration, field));
                            }
                        } else if (binding instanceof IVariable) {
                            CPPMethod method = getCPPMethod();
                            if (method != null) {
                                method.addVariable(new CPPVariable(declarator.getName(), declaration));
                            } else {
                                getCPPFile().addGlobalVariable(new CPPVariable(declarator.getName(), declaration));
                            }
                        } else if (binding instanceof ICPPFunction) {
                            IASTFunctionDeclarator funcDeclarator = (IASTFunctionDeclarator) declarator;
                            CPPClass cppClass = getCPPClass(funcDeclarator.getName());
                            if (cppClass != null) {
                                cppClass.addMethod(new CPPMethod(funcDeclarator));
                            } else {
                                getCPPFile().addFunction(new CPPMethod(funcDeclarator));
                            }
                        }
                    }
                } else if (declaration instanceof ICPPASTFunctionDefinition) {
                    ICPPASTFunctionDefinition functionDefinition = (ICPPASTFunctionDefinition) declaration;
                    functionsDefinitions.push(functionDefinition);
                    IASTFunctionDeclarator funcDeclarator = functionDefinition.getDeclarator();
                    CPPClass cppClass = getCPPClass(funcDeclarator.getName());
                    if (cppClass != null) {
                        cppClass.addMethod(new CPPMethod(functionDefinition));
                    } else {
                        getCPPFile().addFunction(new CPPMethod(functionDefinition));
                    }
                }
            } else {
                if (log.isDebugEnabled()) {
                    log.debug("Skipped declaration  " + declaration + " in file " + declaration.getContainingFilename() + " (current file: " + file.getAbsolutePath() + ")");
                }
            }
        } catch (Throwable e) {
            if (log.isDebugEnabled()) {
                log.debug("An exception was thrown while visiting: " + declaration, e);
            }
        }

        return ASTVisitor.PROCESS_CONTINUE;
    }

    @Override
    public int leave(IASTDeclaration declaration) {
        if (file.equals(new File(declaration.getContainingFilename()))) {
            if (declaration instanceof ICPPASTFunctionDefinition) {
                functionsDefinitions.pop();
            }
        }
        return ASTVisitor.PROCESS_CONTINUE;
    }

    @Override
    public int visit(IASTProblem problem) {
        if (file.equals(new File(problem.getContainingFilename()))) {
            if (log.isWarnEnabled()) {
                log.warn(problem.getMessageWithLocation()); //note: requires dependency on com.ibm.icu
            }
        }
        return ASTVisitor.PROCESS_CONTINUE;
    }

    protected CPPFile getCPPFile() {
        CPPFile cppFile = cppfiles.get(file.getAbsolutePath());
        if (cppFile == null) {
            cppFile = new CPPFile(file.getAbsolutePath());
            cppFile.setTranslationUnit(translationUnit);
            cppfiles.put(cppFile.getName(), cppFile);
        }
        return cppFile;
    }

    protected CPPClass getCPPClass(String name) {
        CPPFile cppFile = getCPPFile();
        CPPClass cppClass = cppFile.getClass(name);
        if (cppClass == null) {
            cppClass = new CPPClass(name, cppFile.getNamespace(getFullNamespace()));
            if (cppClass.getSimpleName().isEmpty()) {
                return null;
            }
            cppFile.addClass(cppClass);
        }
        return cppClass;
    }

    protected CPPClass getCPPClass(ICPPASTCompositeTypeSpecifier type) {
        String n = getFullNamespace();
        if (n.trim().length() > 0) {
            n += "::";
        }
        List<String> parentNames = new ArrayList<String>();
        IASTNode parent = type;
        while ((parent = parent.getParent()) != null) { //TODO: is there a better way to include the containing class names?
            if (parent instanceof ICPPASTCompositeTypeSpecifier) {
                ICPPASTCompositeTypeSpecifier parentType = (ICPPASTCompositeTypeSpecifier) parent;
                parentNames.add(parentType.getName().getLastName().toString());
            }
        }
        for (int i = parentNames.size() - 1; i >= 0; i--) {
            n += parentNames.get(i) + "::";
        }
        n += type.getName().getLastName();
        CPPClass cppClass = getCPPClass(n);
        cppClass.setCompositeTypeSpecifier(type);
        return cppClass;
    }

    protected CPPClass getCPPClass(IASTName name) {
        if (name instanceof ICPPASTQualifiedName) {
            String s = "";
            ICPPASTQualifiedName qname = (ICPPASTQualifiedName) name;
            for (ICPPASTNameSpecifier ns : qname.getQualifier()) {
                s += new String(ns.toCharArray()) + "::";
            }
            if (s.length() > 1) {
                s = s.substring(0, s.length() - 2);
            }
            String ns = getFullNamespace();
            if (ns.trim().length() > 0) {
                s = ns + "::" + s;
            }
            return getCPPClass(s);
        } else {
            if (compositeTypeSpecifiers.size() > 0) {
                ICPPASTCompositeTypeSpecifier type = compositeTypeSpecifiers.peek();
                return getCPPClass(type);
            } else {
                return null;
            }
        }
    }

    protected CPPMethod getCPPMethod() {
        if (functionsDefinitions.size() > 0) {
            ICPPASTFunctionDefinition func = functionsDefinitions.peek();
            IASTFunctionDeclarator funcDeclarator = func.getDeclarator();
            CPPClass cppClass = getCPPClass(funcDeclarator.getName());
            String signature = getFunctionSignature(funcDeclarator);
            if (cppClass != null) {
                return cppClass.getMethod(signature);
            } else {
                return getCPPFile().getFunction(signature);
            }
        }
        return null;
    }

    protected String getFullNamespace() {
        String str = "";
        for (ICPPASTNamespaceDefinition ns : namespaces) {
            str += "" + ns.getName() + "::";
        }
        if (str.length() > 1) {
            str = str.substring(0, str.length() - 2);
        }
        return str;
    }

    protected String getFunctionSignature(IASTFunctionDeclarator functionDeclarator) {
        IASTName astName = functionDeclarator.getName();
        IFunction function = (IFunction) astName.getBinding();
        if (function == null) {
            function = (IFunction) astName.resolveBinding();
        }
        return function.toString();
    }


    private static class FileProvider extends InternalFileContentProvider {
        @Override
        public InternalFileContent getContentForInclusion(String filePath, IMacroDictionary macroDictionary) {
            return (InternalFileContent) InternalFileContent.createForExternalFileLocation(filePath);
        }

        @Override
        public InternalFileContent getContentForInclusion(IIndexFileLocation ifl, String astPath) {
            return null;
        }
    }

//J-
    public static void main(String[] argv) throws Exception {
        File parent = new File("D:\\perforce\\dev\\ayammout\\jcpp\\core\\lang\\src\\main");
        List<File> files = new ArrayList<File>();
        fillFiles(parent, files);

        CPPParser parser = new CPPParser();
        List<String> incs = new ArrayList<String>();
        incs.add("D:\\perforce\\dev\\ayammout\\jcpp\\core\\lang\\src\\main\\include");
        incs.add("D:\\perforce\\dev\\ayammout\\jcpp\\native\\include\\src\\main\\include");
        parser.setIncludes(incs);
        parser.setSymbols(new HashMap<String, String>());

        for (File f : files) {
            System.out.println("Parsing file " + f.getAbsolutePath());
            parser.parse(f);
        }

        CPPFile[] cs = parser.getCPPFiles();
        for (CPPFile c : cs) {
            c.writeTo(System.out);
        }

        Updater updater = new Updater();
        updater.replaceMacro("JCPP_EXPORT", "JCPP_IMPORT");
        for (CPPFile c : cs) {
            UpdatesResult result = updater.update(c);
            System.out.println(result.getContent());
        }
    }

    private static void fillFiles(File f, List<File> files) {
        if (f.isDirectory()) {
            for (File f1 : f.listFiles()) {
                fillFiles(f1, files);
            }
        } else {
            files.add(f);
        }
    }
//J+

}

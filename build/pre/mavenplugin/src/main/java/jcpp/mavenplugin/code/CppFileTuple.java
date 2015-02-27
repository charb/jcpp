package jcpp.mavenplugin.code;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

import jcpp.mavenplugin.code.gc.GcClassCodeGenerator;
import jcpp.mavenplugin.code.gc.GcEndOfNamespaceCodeGenerator;
import jcpp.mavenplugin.code.gc.GcFieldCodeGenerator;
import jcpp.mavenplugin.code.gc.GcFileTupleContext;
import jcpp.mavenplugin.code.gc.GcForLoopVariableCodeGenerator;
import jcpp.mavenplugin.code.gc.GcMemberInitializerCodeGenerator;
import jcpp.mavenplugin.code.gc.GcMethodCodeGenerator;
import jcpp.mavenplugin.code.gc.GcVariableCodeGenerator;
import jcpp.mavenplugin.code.history.ClassHistoryInfo;
import jcpp.mavenplugin.code.history.FileHistory;
import jcpp.mavenplugin.code.history.TupleHistory;
import jcpp.mavenplugin.code.history.TupleHistoryInfo;
import jcpp.mavenplugin.code.reflect.ReflectionClassCodeGenerator;
import jcpp.mavenplugin.code.reflect.ReflectionCodeGenerator;
import jcpp.mavenplugin.code.reflect.ReflectionStartOfNamespaceCodeGenerator;
import jcpp.parser.cpp.CPPClass;
import jcpp.parser.cpp.CPPFile;
import jcpp.parser.cpp.CPPParser;
import jcpp.parser.cpp.update.Updater;
import jcpp.parser.cpp.update.UpdatesResult;

import org.apache.commons.io.FileUtils;
import org.apache.maven.plugin.logging.Log;


public class CppFileTuple implements Comparable<CppFileTuple> {

    public static final String IGNORE_PACKAGE_REFLECTION = "IgnorePackageReflection";

    public static final String JCPP_IMPORT = "JCPP_IMPORT";

    public static final String JCPP_EXPORT = "JCPP_EXPORT";

    public static final String GC_INFO_INCLUDE = "jcpp/gc/info/GcInfoInclude.h";

    private final String name;
    private final String namespace;

    private final CppPackage cppPackage;

    private final File headerFile;
    private CPPFile headerCPPFile;

    private final File cppFile;
    private CPPFile cppCPPFile;

    private UpdaterContext updaterContext;

    private TupleHistory existingTupleHistory;

    private TupleHistory newTupleHistory;

    private GcFileTupleContext gcFileTupleContext;

	public CppFileTuple(String name, String namespace, File headerFile, File cppFile, CppPackage cppPackage) {
        this.name = name;
        this.namespace = namespace;
        this.headerFile = headerFile;
        this.cppFile = cppFile;
        this.cppPackage = cppPackage;

        if (cppPackage != null) {
            cppPackage.addCPPFileTuple(this);
        }
    }


    public void init(UpdaterContext updaterContext, TupleHistory existingTupleHistory) {
        this.updaterContext = updaterContext;
        this.existingTupleHistory = existingTupleHistory;

        if (existingTupleHistory != null) {
            existingTupleHistory.setCppFileTuple(this);
        }
    }
    
    public void clean() {
    	headerCPPFile = null;
    	cppCPPFile = null;
    	gcFileTupleContext = null;
    }

    public boolean checkUpdated() throws IOException {
        if (existingTupleHistory == null) {
            return true;
        }

        FileHistory headerFileHistory = existingTupleHistory.getHeaderFileHistory();
        if (headerFile == null) {
            if (headerFileHistory != null) {
                return true;
            }
        } else {
            if ((headerFileHistory == null) || (!FileHistory.calculateFileCheckSum(headerFile).equals(headerFileHistory.getCrc()))) {
                return true;
            }
        }

        if (!updaterContext.isUpdateIncludeDirOnly()) {
            FileHistory cppFileHistory = existingTupleHistory.getCppFileHistory();
            if (cppFile == null) {
                if (cppFileHistory != null) {
                    return true;
                }
            } else {
                if ((cppFileHistory == null) || (!FileHistory.calculateFileCheckSum(cppFile).equals(cppFileHistory.getCrc()))) {
                    return true;
                }
            }
        }

        return false;
    }

    public void parseFiles() throws Exception {
    	CppParserBuilder parserBuilder = updaterContext.getParserBuilder();
    	
        if (!updaterContext.willUpdate()) {
            return;
        }

        Log log = updaterContext.getLog();
        if ((log != null) && log.isDebugEnabled()) {
            log.debug("Parsing Code files with namespace \"" + namespace + "\" and name \"" + name + "\"");
        }

        if (headerFile != null) {
            CPPParser headerFileParser = parserBuilder.build(headerFile);
            headerCPPFile = findCPPFile(headerFileParser, headerFile);
        }

        if ((cppFile != null) && !updaterContext.isUpdateIncludeDirOnly()) {
            CPPParser cppFileParser = parserBuilder.build(cppFile);
            cppCPPFile = findCPPFile(cppFileParser, cppFile);
        }
        
        if(updaterContext.isAddGCcode()) {
        	gcFileTupleContext = new GcFileTupleContext(headerCPPFile, cppCPPFile);
        }
    }

    public void update() throws Exception {
        Log log = updaterContext.getLog();

        File newHeaderFile = null;
        String headerRelativePath = getHeaderRelativePath(updaterContext.getOriginalHeaderBaseDir().getPath());
        if (headerRelativePath != null) {
            newHeaderFile = new File(updaterContext.getNewHeaderBaseDir(), headerRelativePath);
            UpdatesResult updatedHeaderResult = updateHeaderFile();
            if (updatedHeaderResult != null) {
                if ((log != null) && log.isDebugEnabled()) {
                    log.debug("Writing updated header file to " + newHeaderFile.getPath());
                }
                FileUtils.write(newHeaderFile, updatedHeaderResult.getContent());
            } else {
                if ((log != null) && log.isDebugEnabled()) {
                    log.debug("Copying non updated header file to " + newHeaderFile.getPath());
                }
                if (!headerFile.equals(newHeaderFile)) {
                	FileUtils.copyFile(headerFile, newHeaderFile);
                }
            }
        }

        File newCppFile = null;
        if (!updaterContext.isUpdateIncludeDirOnly()) {
            String cppRelativePath = getCppRelativePath(updaterContext.getOriginalCppBaseDir().getPath());
            if (cppRelativePath != null) {
                newCppFile = new File(updaterContext.getNewCppBaseDir(), cppRelativePath);
                UpdatesResult updatedCppResult = updateCppFile();
                if (updatedCppResult != null) {
                    if ((log != null) && log.isDebugEnabled()) {
                        log.debug("Writing updated cpp file to " + newHeaderFile.getPath());
                    }
                    FileUtils.write(newCppFile, updatedCppResult.getContent());
                } else {
                    if ((log != null) && log.isDebugEnabled()) {
                        log.debug("Copying non updated cpp file to " + newHeaderFile.getPath());
                    }
                    FileUtils.copyFile(cppFile, newCppFile);
                }
            }
        }

        List<CppFileTuple> generatedCode = generateCode();

        newTupleHistory = createTupleHistory(generatedCode);
    }

    public void deleteExistingHistoryFiles() {
        if (existingTupleHistory != null) {
            existingTupleHistory.delete(updaterContext.getNewHeaderBaseDir(), updaterContext.getNewCppBaseDir());
        }
    }

    public TupleHistory getExistingTupleHistory() {
        return existingTupleHistory;
    }

    public TupleHistory getNewTupleHistory() {
        return newTupleHistory;
    }

    public void setNewTupleHistory(TupleHistory newTupleHistory) {
        this.newTupleHistory = newTupleHistory;
    }

    public String getName() {
        return name;
    }

    public String getNamespace() {
        return namespace;
    }

    public CppPackage getCPPPackage() {
        return cppPackage;
    }

    public File getHeaderFile() {
        return headerFile;
    }

    public File getCppFile() {
        return cppFile;
    }

    public CPPFile getHeaderCPPFile() {
        return headerCPPFile;
    }

    public CPPFile getCppCPPFile() {
        return cppCPPFile;
    }
    
    public GcFileTupleContext getGcFileTupleContext() {
		return gcFileTupleContext;
	}

    public String getHeaderRelativePath(String baseDirectory) throws IOException {
        return (headerFile == null) ? null : headerFile.getCanonicalPath().substring(baseDirectory.length() + 1);
    }

    public String getCppRelativePath(String baseDirectory) throws IOException {
        return (cppFile == null) ? null : cppFile.getCanonicalPath().substring(baseDirectory.length() + 1);
    }

    public CPPFile findCPPFile(CPPParser parser, File sourceFile) {
        for (CPPFile cppFile : parser.getCPPFiles()) {
            if (sourceFile.equals(new File(cppFile.getName()))) {
                return cppFile;
            }
        }
        return null;
    }

    public UpdaterContext getUpdaterContext() {
        return updaterContext;
    }

    @Override
    public int compareTo(CppFileTuple o) {
        return name.compareTo(o.name);
    }

    @Override
    public String toString() {
        return (new StringBuilder()).append("CPP File Tuple (H:").append((headerFile == null) ? "N" : "Y").append(",CPP:").append((cppFile == null) ? "N" : "Y").append(") namespace: ").append(namespace).append(" name: ")
            .append(name).toString();
    }

    protected UpdatesResult updateHeaderFile() throws Exception {
        Updater updater = (headerCPPFile == null) ? null : buildFileUpdater(updaterContext, true);
        return (updater == null) ? null : updater.update(headerCPPFile);
    }

    protected UpdatesResult updateCppFile() throws Exception {
        Updater updater = (cppCPPFile == null) ? null : buildFileUpdater(updaterContext, false);
        return (updater == null) ? null : updater.update(cppCPPFile);
    }

    protected List<CppFileTuple> generateCode() throws Exception {
        List<CppFileTuple> generatedTuples = new ArrayList<CppFileTuple>();

        List<ICppCodeGenerator<CppFileTuple>> codeGenerators = createCppCodeGenerators();
        for (ICppCodeGenerator<CppFileTuple> codeGenerator : codeGenerators) {
            CppFileTuple generatedTuple = codeGenerator.generateCode(updaterContext, this);
            if (generatedTuple != null) {
                generatedTuples.add(generatedTuple);
            }
        }

        return generatedTuples;
    }

    protected TupleHistory createTupleHistory(List<CppFileTuple> generatedCode) throws Exception {
        if ((headerFile == null) && (cppFile == null)) {
            throw new IllegalArgumentException("Null header and cpp files!");
        }

        FileHistory headerFileHistory = null;
        if (headerFile != null) {
            String headerPath = Utils.getFileRelativePath(headerFile, updaterContext.getOriginalHeaderBaseDir());
            headerFileHistory = new FileHistory(headerPath, headerFile);
        }

        FileHistory cppFileHistory = null;
        if (cppFile != null) {
            String cppPath = Utils.getFileRelativePath(cppFile, updaterContext.getOriginalCppBaseDir());
            cppFileHistory = new FileHistory(cppPath, cppFile);
        }

        TupleHistory tupleHistory = new TupleHistory(name, namespace, headerFileHistory, cppFileHistory);

        if ((generatedCode != null) && (generatedCode.size() > 0)) {
            for (CppFileTuple generatedCppFileTuple : generatedCode) {
                tupleHistory.addGeneratedTuplsHistory(generatedCppFileTuple.createTupleHistory(null));
            }
        }

        tupleHistory.setTupleHistoryInfo(createTupleHistoryInfo());

        return tupleHistory;
    }

    @SuppressWarnings("unchecked")
    protected Updater buildFileUpdater(UpdaterContext updaterContext, boolean headerUpdater) {
        Updater updater = new Updater();
        boolean updateFactoryAdded = false;

        if (updaterContext.isUpdateExportMacro()) {
            updater.replaceMacro(JCPP_EXPORT, JCPP_IMPORT);
            updateFactoryAdded = true;
        }

        if (updaterContext.isAddGCcode()) {
        	gcFileTupleContext.setHeaderUpdater(headerUpdater);
        	
            updater.insertIncludes(Arrays.asList(GC_INFO_INCLUDE));

            updater.addClassCodeGenerator(new GcClassCodeGenerator(gcFileTupleContext), Collections.EMPTY_LIST);
            updater.addFieldCodeGenerator(new GcFieldCodeGenerator(gcFileTupleContext), Collections.EMPTY_LIST);
            updater.addEndOfNamespaceCodeGenerator(new GcEndOfNamespaceCodeGenerator(gcFileTupleContext), Collections.EMPTY_LIST);
            updater.addMemberInitializerCodeGenerator(new GcMemberInitializerCodeGenerator(gcFileTupleContext), Collections.EMPTY_LIST);
            updater.addMethodCodeGenerator(new GcMethodCodeGenerator(gcFileTupleContext), Collections.EMPTY_LIST);
            updater.addVariableCodeGenerator(new GcVariableCodeGenerator(gcFileTupleContext), Collections.EMPTY_LIST);
            updater.addForStatementInitializerVariableCodeGenerator(new GcForLoopVariableCodeGenerator(gcFileTupleContext), Collections.EMPTY_LIST);
            updateFactoryAdded = true;
        }

        if (updaterContext.isAddReflectionCode()) {
            if (headerUpdater) {
                updater.addClassCodeGenerator(new ReflectionClassCodeGenerator(headerCPPFile), Collections.EMPTY_LIST);
                updater.addStartOfNamespaceCodeGenerator(new ReflectionStartOfNamespaceCodeGenerator(headerCPPFile), Collections.EMPTY_LIST);
            } else {
                updater.addClassCodeGenerator(new ReflectionClassCodeGenerator(cppCPPFile), Collections.EMPTY_LIST);
                updater.insertEndOfFileIncludes(Arrays.asList(Utils.createRelativeReflectionHeaderFilePath(this)));
                updater.addStartOfNamespaceCodeGenerator(new ReflectionStartOfNamespaceCodeGenerator(cppCPPFile), Collections.EMPTY_LIST);
            }
            updateFactoryAdded = true;
        }

        return updateFactoryAdded ? updater : null;
    }

    protected List<ICppCodeGenerator<CppFileTuple>> createCppCodeGenerators() {
        List<ICppCodeGenerator<CppFileTuple>> list = new ArrayList<ICppCodeGenerator<CppFileTuple>>();

        if (updaterContext.isAddReflectionCode()) {
            list.add(ReflectionCodeGenerator.getInstance());
        }

        return list;
    }

    protected TupleHistoryInfo createTupleHistoryInfo() {
        TupleHistoryInfo tupleHistoryInfo = new TupleHistoryInfo(name, namespace);

        if (headerCPPFile != null) {
            for (CPPClass cppClass : headerCPPFile.getClasses()) {
                if (!Utils.isDeclaredClass(cppClass) && (cppClass.getAnnotation(IGNORE_PACKAGE_REFLECTION) == null)) {
                    tupleHistoryInfo.addClassHistoryInfo(new ClassHistoryInfo(cppClass.getSimpleName(), cppClass.getNamespaceName()));
                }
            }
        }

        return tupleHistoryInfo;
    }

}

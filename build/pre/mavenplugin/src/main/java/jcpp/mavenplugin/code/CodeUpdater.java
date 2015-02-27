package jcpp.mavenplugin.code;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

import jcpp.mavenplugin.code.history.CodeHistory;
import jcpp.mavenplugin.code.history.PackageHistory;
import jcpp.mavenplugin.code.history.TupleHistory;

import org.apache.commons.io.FileUtils;
import org.apache.maven.plugin.logging.Log;
import org.apache.maven.project.MavenProject;


public class CodeUpdater {

    public static final String CODE_HISTORY_XML = "CodeHistory.xml";

    protected final UpdaterContext updaterContext;

    protected final CppPackageGenerator cppFileTupleGenerator;

    protected final CodeHistory existingCodeHistory;

    protected final File newSrcDir;

    protected final File codeHistoryFile;

    protected final Log log;

    private final boolean usingHistoryDir;


    public CodeUpdater(MavenProject mavenProject, Log log, File srcDir, File newSrcDir, File codeHistoryFile, File codeHistoryDirectory, boolean updateIncludeDirOnly, boolean updateExportMacro, boolean addGCcode,
        boolean addReflectionCode, String generatedCodePrefix) throws IOException {

        srcDir = srcDir.getCanonicalFile();
        newSrcDir = newSrcDir.getCanonicalFile();

        this.log = log;
        this.newSrcDir = newSrcDir;
        this.codeHistoryFile = (codeHistoryFile == null) ? ((codeHistoryDirectory == null) ? null : new File(codeHistoryDirectory, CODE_HISTORY_XML)) : codeHistoryFile;

        existingCodeHistory = readExistingCodeHistory();

        updaterContext = new UpdaterContext(mavenProject, log, updateExportMacro, addGCcode, addReflectionCode, updateIncludeDirOnly, srcDir, newSrcDir, codeHistoryDirectory, generatedCodePrefix);

        cppFileTupleGenerator = new CppPackageGenerator(updaterContext.getOriginalHeaderBaseDir(), updaterContext.getOriginalCppBaseDir());

        usingHistoryDir = codeHistoryDirectory != null;
    }


    // ----------------------------------------------------------
    // Update Method
    // ----------------------------------------------------------

    public void update() throws Exception {
        if ((log != null) && log.isDebugEnabled()) {
            log.debug("\n\n");
            log.debug(">>> -------------------------------------------------------------------------------- <<<");
            log.debug(">>> Starting CPP Code Updater [Export Macro = " + updaterContext.isUpdateExportMacro() + "] [GC = " + updaterContext.isAddGCcode() + "] [Reflection = " + updaterContext.isAddReflectionCode() + "]");
            log.debug(">>> -------------------------------------------------------------------------------- <<<");
            log.debug("\n\n");
        }

        CppPackage cppPackage = cppFileTupleGenerator.generateCPPPackage();
        cppPackage.init(updaterContext, (existingCodeHistory == null) ? null : existingCodeHistory.getPackageHistory());

        initializeNewSrcDirectory();

        CodeUpdaterCppPackageVisitor visitor = new CodeUpdaterCppPackageVisitor();
        try {
        	cppPackage.accept(visitor);
        } finally {
        	visitor.clean();	
        }

        if (usingHistoryDir) {
            createHistoryDirectory();
        } else {
            deleteLeftOverHistory();
        }

        copyNonCodeFiles();

        writeCodeHistory(cppPackage);

        if ((log != null) && log.isDebugEnabled()) {
            log.debug("\n\n");
            log.debug(">>> -------------------------------------------------------------------------------- <<<");
            log.debug(">>> End of  CPP Code Updater ");
            log.debug(">>> -------------------------------------------------------------------------------- <<<");
            log.debug("\n\n");
        }

    }

    // ----------------------------------------------------------
    // Copy Non Code Files
    // ----------------------------------------------------------

    protected void copyNonCodeFiles() throws IOException {
        copyNonCodeFiles(updaterContext.getOriginalHeaderBaseDir(), updaterContext.getNewHeaderBaseDir(), updaterContext.getOriginalHeaderBaseDir());
        if (!updaterContext.isUpdateIncludeDirOnly()) {
            copyNonCodeFiles(updaterContext.getOriginalCppBaseDir(), updaterContext.getNewCppBaseDir(), updaterContext.getOriginalCppBaseDir());
        }
    }

    protected void copyNonCodeFiles(File originalBaseDir, File newBaseDir, File file) throws IOException {
        File[] listFiles = file.listFiles();
        if (listFiles == null) {
            return;
        }
        for (File childFile : listFiles) {
            if (childFile.isDirectory()) {
                copyNonCodeFiles(originalBaseDir, newBaseDir, childFile);
            } else if (!Utils.isCodeFile(childFile)) {
                File newFile = new File(newBaseDir, Utils.getFileRelativePath(childFile, originalBaseDir));
                newFile.getParentFile().mkdirs();
                if ((log != null) && log.isDebugEnabled()) {
                    log.debug("Copying non code file from " + childFile.getPath() + " to " + newFile.getPath());
                }
                FileUtils.copyFile(childFile, newFile);
            }
        }
    }

    // ----------------------------------------------------------
    // History Methods
    // ----------------------------------------------------------

    protected void deleteNonHistoryFiles(File baseDir, File file, boolean headerDir) throws IOException {
        File[] listFiles = file.listFiles();
        if (listFiles == null) {
            return;
        }
        for (File childFile : listFiles) {
            if (existingCodeHistory == null) {
                if ((log != null) && log.isDebugEnabled()) {
                    log.debug("Deleting File " + childFile.getPath() + " because existing code history is null");
                }
                FileUtils.deleteQuietly(childFile);
            } else {
                if (childFile.isDirectory()) {
                    deleteNonHistoryFiles(baseDir, childFile, headerDir);
                } else {
                    String namespace = Utils.getNamespace(childFile, baseDir);
                    String name = Utils.getCodeClassName(childFile);

                    TupleHistory tupleHistory = existingCodeHistory.findTupleHistory(namespace, name);
                    if (tupleHistory == null) {
                        TupleHistory generatedTupleHistory = existingCodeHistory.findGeneratedTupleHistory(namespace, name);
                        if (generatedTupleHistory == null) {
                            if ((log != null) && log.isDebugEnabled()) {
                                log.debug("Deleting File " + childFile.getPath() + " because no history exist for it");
                            }
                            FileUtils.deleteQuietly(childFile);
                        }
                    } else {
                        if (headerDir) {
                            if (tupleHistory.getHeaderFileHistory() == null) {
                                if ((log != null) && log.isDebugEnabled()) {
                                    log.debug("Deleting File " + childFile.getPath() + " because no header file history exist for it");
                                }
                                FileUtils.deleteQuietly(childFile);
                            }
                        } else {
                            if (tupleHistory.getCppFileHistory() == null) {
                                if ((log != null) && log.isDebugEnabled()) {
                                    log.debug("Deleting File " + childFile.getPath() + " because no cpp file history exist for it");
                                }
                                FileUtils.deleteQuietly(childFile);
                            }
                        }
                    }
                }
            }
        }
    }

    protected void deleteLeftOverHistory() {
        if (existingCodeHistory != null) {
            if ((log != null) && log.isDebugEnabled()) {
                log.debug("Deleting left over history.");
            }
            existingCodeHistory.deleteLeftOverHistory(updaterContext.getNewHeaderBaseDir(), updaterContext.getNewCppBaseDir());
        }
    }

    protected void createHistoryDirectory() throws IOException {
        FileUtils.deleteQuietly(updaterContext.getHistoryHeaderBaseDir());
        if (updaterContext.getNewHeaderBaseDir().exists()) {
            FileUtils.copyDirectory(updaterContext.getNewHeaderBaseDir(), updaterContext.getHistoryHeaderBaseDir());
        }
        if (!updaterContext.isUpdateIncludeDirOnly()) {
            FileUtils.deleteQuietly(updaterContext.getHistoryCppBaseDir());
            if (updaterContext.getNewCppBaseDir().exists()) {
                FileUtils.copyDirectory(updaterContext.getNewCppBaseDir(), updaterContext.getHistoryCppBaseDir());
            }
        }
    }

    protected void writeCodeHistory(CppPackage rootCppPackage) {
        CodeHistory codeHistory = new CodeHistory(rootCppPackage.getNewPackageHistory());
        if ((log != null) && log.isDebugEnabled()) {
            log.debug("Writing Code History to file: " + codeHistoryFile.getPath());
        }
        try {
            codeHistory.writeToFile(codeHistoryFile);
        } catch (Exception e) {
            if ((log != null) && log.isErrorEnabled()) {
                log.error("An exception was thrown while writing code history to file: " + codeHistoryFile.getPath(), e);
            }
        }
    }

    protected CodeHistory readExistingCodeHistory() {
        if (codeHistoryFile.exists() && codeHistoryFile.isFile()) {
            try {
                CodeHistory codeHistory = CodeHistory.readFromFile(codeHistoryFile);
                if (codeHistory != null) {
                    codeHistory.sort();
                    if ((log != null) && log.isDebugEnabled()) {
                        log.debug("Successfully read code history from file " + codeHistoryFile.getPath());
                    }
                }
                return codeHistory;
            } catch (Exception e) {
                if ((log != null) && log.isErrorEnabled()) {
                    log.error("Failed to read code history file under path = " + codeHistoryFile.getAbsolutePath(), e);
                }
            }
        }
        return null;
    }

    // ----------------------------------------------------------
    // Initialize New Src Directory
    // ----------------------------------------------------------

    protected void initializeNewSrcDirectory() throws IOException {
        if (usingHistoryDir) {
            FileUtils.deleteQuietly(updaterContext.getNewHeaderBaseDir());
            if (!updaterContext.isUpdateIncludeDirOnly()) {
                FileUtils.deleteQuietly(updaterContext.getNewCppBaseDir());
            }
        } else {
            deleteNonHistoryFiles(updaterContext.getNewHeaderBaseDir(), updaterContext.getNewHeaderBaseDir(), true);
            if (!updaterContext.isUpdateIncludeDirOnly()) {
                deleteNonHistoryFiles(updaterContext.getNewCppBaseDir(), updaterContext.getNewCppBaseDir(), false);
            }
        }
    }


    // ----------------------------------------------------------
    // Code Updater Cpp Package Visitor
    // ----------------------------------------------------------

    private class CodeUpdaterCppPackageVisitor implements ICppPackageVisitor {
        private ExecutorService parseThreadPool;

		public CodeUpdaterCppPackageVisitor() {
			parseThreadPool = Executors.newFixedThreadPool(Runtime.getRuntime().availableProcessors());
        }

		public void clean() {
			parseThreadPool.shutdown();
		}
		
        @Override
        public void startCppPackage(CppPackage cppPackage) {
        }
        
		@Override
		public void visitCppFileTuple(CppFileTuple cppFileTuple) {
		}

        @Override
        public void endCppPackage(CppPackage cppPackage) {
        	List<CppFileTuple> cppFileTuples = cppPackage.getCppFileTuples();
        	List<Future<?>> futures = new ArrayList<Future<?>>();
        	for(final CppFileTuple fileTuple : cppFileTuples) {
        		futures.add(parseThreadPool.submit(new Runnable() {
					@Override
					public void run() {
						parseCppFileTuple(fileTuple);
					}
				}));
        	}
        	
        	for(Future<?> future : futures) {
        		try {
					future.get();
				} catch (Throwable e) {
					throw new RuntimeException(e);
				}
        	}
        	
            try {
                if (cppPackage.checkUpdated()) {
                    if (!usingHistoryDir) {
                        cppPackage.deleteExistingHistoryFiles();
                    }
                    cppPackage.update();
                } else {
                    PackageHistory newPackageHistory = cppPackage.createNewHistoryFromExisting();
                    cppPackage.setNewPackageHistory(newPackageHistory);
                    if (usingHistoryDir) {
                        newPackageHistory.copyGeneratedTuples(updaterContext.getHistoryHeaderBaseDir(), updaterContext.getHistoryCppBaseDir(), updaterContext.getNewHeaderBaseDir(), updaterContext.getNewCppBaseDir(),
                            updaterContext.isUpdateIncludeDirOnly());
                    }
                }
            } catch (Exception exception) {
                throw new RuntimeException(exception);
            }
            
            for(CppFileTuple fileTuple : cppFileTuples) {
            	fileTuple.clean();
            }
        }

        private void parseCppFileTuple(CppFileTuple tuple) {
            try {
                if (tuple.checkUpdated()) {
                    if (!usingHistoryDir) {
                        tuple.deleteExistingHistoryFiles();
                    }
                    tuple.parseFiles();
                    tuple.update();
                } else {
                    TupleHistory existingTupleHistory = tuple.getExistingTupleHistory();
                    tuple.setNewTupleHistory(existingTupleHistory);
                    if (usingHistoryDir) {
                        existingTupleHistory.copy(updaterContext.getHistoryHeaderBaseDir(), updaterContext.getHistoryCppBaseDir(), updaterContext.getNewHeaderBaseDir(), updaterContext.getNewCppBaseDir(),
                            updaterContext.isUpdateIncludeDirOnly());
                    }
                }
            } catch (Exception exception) {
                throw new RuntimeException(exception);
            }
        }

    }

}

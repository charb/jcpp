package jcpp.mavenplugin.code;

import java.io.File;

import org.apache.maven.plugin.logging.Log;


public class UpdaterContext {

    public static final String CPP_DIR = "c++";
    public static final String INCLUDE_DIR = "include";

    private final Log log;

    private final boolean updateExportMacro;

    private final boolean addGCcode;

    private final boolean addReflectionCode;

    private final boolean updateIncludeDirOnly;

    private final File newHeaderBaseDir;
    private final File newCppBaseDir;

    private final File originalHeaderBaseDir;
    private final File originalCppBaseDir;

    private final File historyHeaderBaseDir;
    private final File historyCppBaseDir;

    private final String generatedCodePrefix;


    public UpdaterContext(Log log, boolean updateExportMacro, boolean addGCcode, boolean addReflectionCode, boolean updateIncludeDirOnly, File srcDir, File newSrcDir, File codeHistoryDirectory, String generatedCodePrefix) {
        this.log = log;
        this.updateExportMacro = updateExportMacro;
        this.addGCcode = addGCcode;
        this.addReflectionCode = addReflectionCode;
        this.updateIncludeDirOnly = updateIncludeDirOnly;

        this.originalHeaderBaseDir = new File(srcDir, INCLUDE_DIR);
        this.originalCppBaseDir = new File(srcDir, CPP_DIR);

        this.newHeaderBaseDir = new File(newSrcDir, INCLUDE_DIR);
        this.newCppBaseDir = new File(newSrcDir, CPP_DIR);

        this.historyHeaderBaseDir = (codeHistoryDirectory != null) ? new File(codeHistoryDirectory, INCLUDE_DIR) : null;
        this.historyCppBaseDir = (codeHistoryDirectory != null) ? new File(codeHistoryDirectory, CPP_DIR) : null;

        this.generatedCodePrefix = generatedCodePrefix;
    }


    public Log getLog() {
        return log;
    }

    public boolean isUpdateIncludeDirOnly() {
        return updateIncludeDirOnly;
    }

    public boolean isUpdateExportMacro() {
        return updateExportMacro;
    }

    public boolean isAddGCcode() {
        return addGCcode;
    }

    public boolean isAddReflectionCode() {
        return addReflectionCode;
    }

    public boolean willUpdate() {
        return updateExportMacro || addGCcode || addReflectionCode;
    }

    public File getNewHeaderBaseDir() {
        return newHeaderBaseDir;
    }

    public File getNewCppBaseDir() {
        return newCppBaseDir;
    }

    public File getOriginalHeaderBaseDir() {
        return originalHeaderBaseDir;
    }

    public File getOriginalCppBaseDir() {
        return originalCppBaseDir;
    }

    public File getHistoryHeaderBaseDir() {
        return historyHeaderBaseDir;
    }

    public File getHistoryCppBaseDir() {
        return historyCppBaseDir;
    }

    public String getGeneratedCodePrefix() {
        return generatedCodePrefix;
    }

}

package jcpp.mavenplugin.code;

import java.io.File;

import org.apache.maven.plugin.logging.Log;
import org.apache.maven.project.MavenProject;


public class UpdaterContext {

    public static final String CPP_DIR = "c++";
    public static final String INCLUDE_DIR = "include";

    private final Log log;

    private final boolean updateExportMacro;

    private final boolean addGCcode;

    private final boolean addReflectionCode;

    private final boolean updateIncludeDirOnly;

	private final File srcDir;
	private final File newSrcDir;

    private final File originalHeaderBaseDir;
    private final File originalCppBaseDir;
    
    private final File newHeaderBaseDir;
    private final File newCppBaseDir;
	
    private final File historyHeaderBaseDir;
    private final File historyCppBaseDir;

    private final String generatedCodePrefix;
    
    private final CppParserBuilder parserBuilder;
    

    public UpdaterContext(MavenProject mavenProject, Log log, boolean updateExportMacro, boolean addGCcode, boolean addReflectionCode, boolean updateIncludeDirOnly, File srcDir, File newSrcDir, File codeHistoryDirectory, String generatedCodePrefix) {
        this.log = log;
        this.updateExportMacro = updateExportMacro;
        this.addGCcode = addGCcode;
        this.addReflectionCode = addReflectionCode;
        this.updateIncludeDirOnly = updateIncludeDirOnly;
        
		this.srcDir = srcDir;
		this.newSrcDir = newSrcDir;

        this.originalHeaderBaseDir = new File(srcDir, INCLUDE_DIR);
        this.originalCppBaseDir = new File(srcDir, CPP_DIR);

        this.newHeaderBaseDir = new File(newSrcDir, INCLUDE_DIR);
        this.newCppBaseDir = new File(newSrcDir, CPP_DIR);

        this.historyHeaderBaseDir = (codeHistoryDirectory != null) ? new File(codeHistoryDirectory, INCLUDE_DIR) : null;
        this.historyCppBaseDir = (codeHistoryDirectory != null) ? new File(codeHistoryDirectory, CPP_DIR) : null;

        this.generatedCodePrefix = generatedCodePrefix;
        
        parserBuilder = new CppParserBuilder();
        parserBuilder.setLog(log).setMavenProject(mavenProject).setIncludeSrcDirectory(originalHeaderBaseDir);
    }
    
    public UpdaterContext(UpdaterContext originalUpdaterContext, boolean updateExportMacro, boolean addGCcode, boolean addReflectionCode, File srcDir, File newSrcDir, File originalHeaderBaseDir, File originalCppBaseDir, File newHeaderBaseDir, File newCppBaseDir) {
        this.log = originalUpdaterContext.getLog();
        this.updateExportMacro = updateExportMacro;
        this.addGCcode = addGCcode;
        this.addReflectionCode = addReflectionCode;
        this.updateIncludeDirOnly = originalUpdaterContext.isUpdateIncludeDirOnly();
        
		this.srcDir = srcDir;
		this.newSrcDir = newSrcDir;

        this.originalHeaderBaseDir = originalHeaderBaseDir;
        this.originalCppBaseDir = originalCppBaseDir;

        this.newHeaderBaseDir = newHeaderBaseDir;
        this.newCppBaseDir = newCppBaseDir;

        this.historyHeaderBaseDir = originalUpdaterContext.getHistoryHeaderBaseDir();
        this.historyCppBaseDir = originalUpdaterContext.getHistoryCppBaseDir();

        this.generatedCodePrefix = originalUpdaterContext.getGeneratedCodePrefix();
        
        parserBuilder = new CppParserBuilder();
        parserBuilder.setLog(log).setMavenProject(originalUpdaterContext.getParserBuilder().getMavenProject()).setIncludeSrcDirectory(originalHeaderBaseDir);
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

	public File getSrcDir() {
		return srcDir;
	}

	public File getNewSrcDir() {
		return newSrcDir;
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

	public CppParserBuilder getParserBuilder() {
		return parserBuilder;
	}

}

package jcpp.mavenplugin;

import java.io.File;

import jcpp.mavenplugin.code.CodeUpdater;

import org.apache.maven.plugin.AbstractMojo;
import org.apache.maven.plugin.MojoExecutionException;
import org.apache.maven.project.MavenProject;


/**
 * @goal                         pre-compilation
 * @phase                        process-sources
 * @requiresProject
 * @requiresDependencyResolution compile
 */
public class PreCompilationMojo extends AbstractMojo {

    /**
     * @parameter default-value="false"
     * @required
     */
    private boolean addGcCode;

    /**
     * @parameter default-value="false"
     * @required
     */
    private boolean addReflectionCode;

    /**
     * @parameter default-value="${basedir}/src/main"
     * @required
     */
    private File sourceDirectory;

    /**
     * @parameter default-value="${project.build.directory}/newsrc/main"
     * @required
     */
    private File targetSourceDirectory;

    /**
     * @parameter default-value="${basedir}/src/test"
     * @required
     */
    private File testSourceDirectory;

    /**
     * @parameter default-value="${project.build.directory}/newsrc/test"
     * @required
     */
    private File targetTestSourceDirectory;

    /**
     * @parameter default-value="${project}"
     * @readonly
     * @required
     */
    private MavenProject mavenProject;


    public PreCompilationMojo() {
    }


    @Override
    public final void execute() throws MojoExecutionException {
        try {
            processSources(sourceDirectory, targetSourceDirectory);
        } catch (Exception e) {
            getLog().error("Error while processing test sources", e);
            throw new MojoExecutionException("Error while processing test sources", e);
        }

        try {
            processSources(testSourceDirectory, targetTestSourceDirectory);
        } catch (Exception e) {
            getLog().error("Error while processing sources", e);
            throw new MojoExecutionException("Error while processing sources", e);
        }
    }

    protected void processSources(File srcDir, File newSrcDir) throws MojoExecutionException, Exception {
        File codeHistoryFile = new File(newSrcDir, CodeUpdater.CODE_HISTORY_XML);
        String generatedCodePrefix = (mavenProject.getGroupId().replace(".", "_") + "_" + mavenProject.getArtifactId().replace(".", "_").replace("-", "_") + "_").toUpperCase();
        CodeUpdater cppCodeUpdater = new CodeUpdater(mavenProject, getLog(), srcDir, newSrcDir, codeHistoryFile, null, false, false, addGcCode, addReflectionCode, generatedCodePrefix);
        cppCodeUpdater.update();
    }

}

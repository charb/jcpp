package jcpp.mavenplugin;

import java.io.File;

import jcpp.mavenplugin.code.CodeUpdater;
import jcpp.mavenplugin.code.Utils;

import org.apache.maven.plugin.AbstractMojo;
import org.apache.maven.plugin.MojoExecutionException;
import org.apache.maven.project.MavenProject;


/**
 * @goal                         post-compilation
 * @phase                        prepare-package
 * @requiresProject
 * @requiresDependencyResolution compile
 */
public class PostCompilationMojo extends AbstractMojo {

    /**
     * @parameter default-value="${project.build.directory}/newsrc/main"
     * @required
     */
    private File sourceDirectory;

    /**
     * @parameter default-value="${project.build.directory}/nar"
     * @required
     */
    private File targetSourceDirectory;

    /**
     * @parameter default-value="${project.build.directory}/history-nar"
     * @required
     */
    private File historyDirectory;

    /**
     * @parameter default-value="${project}"
     * @readonly
     * @required
     */
    private MavenProject mavenProject;


    public PostCompilationMojo() {
    }


    @Override
    public final void execute() throws MojoExecutionException {
        try {
            File newSrdDir = Utils.getNoArchDirectory(targetSourceDirectory, mavenProject);
            CodeUpdater cppCodeUpdater = new CodeUpdater(mavenProject, getLog(), sourceDirectory, newSrdDir, null, historyDirectory, true, true, false, false, null);
            cppCodeUpdater.update();
        } catch (Exception e) {
            getLog().error("Error while processing sources", e);
            throw new MojoExecutionException("Error while processing sources", e);
        }
    }

}

package jcpp.mavenplugin.code;

import java.io.File;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

import jcpp.parser.cpp.CPPParser;

import org.apache.maven.artifact.Artifact;
import org.apache.maven.plugin.logging.Log;
import org.apache.maven.project.MavenProject;


@SuppressWarnings("rawtypes")
public class CppParserBuilder {

    private MavenProject mavenProject;

    private Log log;

    private List<String> includes;

    private Map<String, String> symbols;

    private File includeSrcDirectory;


    public CppParserBuilder() {
        symbols = new HashMap<String, String>();
    }


    public File getIncludeSrcDirectory() {
        return includeSrcDirectory;
    }

    public CppParserBuilder setIncludeSrcDirectory(File includeSrcDirectory) {
        this.includeSrcDirectory = includeSrcDirectory;
        return this;
    }

    public MavenProject getMavenProject() {
        return mavenProject;
    }

    public CppParserBuilder setMavenProject(MavenProject mavenProject) {
        this.mavenProject = mavenProject;
        return this;
    }

    public Log getLog() {
        return log;
    }

    public CppParserBuilder setLog(Log log) {
        this.log = log;
        return this;
    }

    public CppParserBuilder addSymbol(String name, String value) {
        symbols.put(name, value);
        return this;
    }

    public Map<String, String> getSymbols() {
        return symbols;
    }

    public CPPParser build(File sourceFile) throws Exception {
        if (includes == null) {
            init();
        }

        CPPParser cppParser = new CPPParser();
        cppParser.setIncludes(includes);
        cppParser.setSymbols(symbols);
        cppParser.parse(sourceFile);

        return cppParser;
    }

    protected CppParserBuilder init() {
        includes = new ArrayList<String>();
        if (includeSrcDirectory != null) {
            includes.add(includeSrcDirectory.getAbsolutePath());
        }
        includes.addAll(getIncludeDependencies());

        for (String s : includes) {
            if ((log != null) && log.isDebugEnabled()) {
                log.debug("Using include path :" + s);
            }
        }

        return this;
    }

    protected File getTargetNarDirectory() {
        return new File(mavenProject.getBuild().getDirectory() + "/nar");
    }

    protected File getTargetTestNarDirectory() {
        return new File(mavenProject.getBuild().getDirectory() + "/test-nar");
    }

    protected List<Artifact> getNarArtifacts() {
        List<Artifact> narDependencies = new LinkedList<Artifact>();
        for (Iterator i = mavenProject.getArtifacts().iterator(); i.hasNext();) {
            Artifact dependency = (Artifact) i.next();
            if (dependency.getType().equals("nar")) {
                narDependencies.add(dependency);
            }
        }
        return narDependencies;
    }

    protected List<String> getIncludeDependencies() {
        List<String> includes = new ArrayList<String>();
        List<Artifact> dependencies = getNarArtifacts();
        for (Iterator<Artifact> i = dependencies.iterator(); i.hasNext();) {
            Artifact narDependency = i.next();
            File include = Utils.getIncludeDirectory(getTargetNarDirectory(), narDependency.getArtifactId(), narDependency.getBaseVersion());
            if ((log != null) && log.isDebugEnabled()) {
                log.debug("Looking for include directory: " + include.getAbsolutePath());
            }
            if (include.exists()) {
                includes.add(include.getPath());
            } else {
                if ((log != null) && log.isDebugEnabled()) {
                    log.debug("Path " + include.getAbsolutePath() + " does not exist.");
                }
            }
        }
        return includes;
    }

}

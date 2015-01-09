package jcpp.mavenplugin.code;

import java.io.File;
import java.io.FileWriter;

import java.util.HashMap;
import java.util.Map;

import freemarker.cache.ClassTemplateLoader;

import freemarker.template.Configuration;
import freemarker.template.Template;


public abstract class TemplateCodeGenerator<T> implements ICppCodeGenerator<T> {

    protected static final String MODEL = "model";

    protected final Template headerTemplate;
    protected final Template cppTemplate;


    protected TemplateCodeGenerator(String headerTemplateResource, String cppTemplateResource) throws Exception {
        Configuration config = new Configuration(Configuration.VERSION_2_3_21);
        config.setTemplateLoader(new ClassTemplateLoader(TemplateCodeGenerator.class, "/"));

        headerTemplate = (headerTemplateResource == null) ? null : config.getTemplate(headerTemplateResource);
        cppTemplate = (cppTemplateResource == null) ? null : config.getTemplate(cppTemplateResource);
    }


    protected abstract String createRelativeHeaderFilePath(T t);

    protected abstract String createRelativeCppFilePath(T t);

    protected File generateHeaderFile(UpdaterContext updaterContext, Object headerModel, T t) throws Exception {
        return (headerTemplate == null) ? null : generateCodeFromTemplate(headerTemplate, headerModel, updaterContext.getNewCppBaseDir(), createRelativeHeaderFilePath(t));
    }

    protected File generateCppFile(UpdaterContext updaterContext, Object cppModel, T t) throws Exception {
        return (cppTemplate == null) ? null : generateCodeFromTemplate(cppTemplate, cppModel, updaterContext.getNewCppBaseDir(), createRelativeCppFilePath(t));
    }

    protected File generateCodeFromTemplate(Template template, Object model, File baseDir, String relativePath) throws Exception {
        File generatedFile = null;
        if (model != null) {
            Map<String, Object> dataModel = new HashMap<String, Object>();
            dataModel.put(MODEL, model);

            generatedFile = new File(baseDir, relativePath);

            FileWriter generatedFileWriter = new FileWriter(generatedFile);
            try {
                template.process(dataModel, generatedFileWriter);
            } finally {
                generatedFileWriter.close();
            }
        }
        return generatedFile;
    }

}

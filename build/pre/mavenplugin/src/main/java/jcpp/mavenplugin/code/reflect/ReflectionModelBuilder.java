package jcpp.mavenplugin.code.reflect;

import java.io.File;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;

import jcpp.mavenplugin.code.CppFileTuple;
import jcpp.mavenplugin.code.UpdaterContext;
import jcpp.mavenplugin.code.Utils;

import jcpp.parser.cpp.CPPAnnotation;
import jcpp.parser.cpp.CPPBaseClass;
import jcpp.parser.cpp.CPPClass;
import jcpp.parser.cpp.CPPClassForwardDeclaration;
import jcpp.parser.cpp.CPPField;
import jcpp.parser.cpp.CPPFile;
import jcpp.parser.cpp.CPPMethod;
import jcpp.parser.cpp.CPPMethodParameter;
import jcpp.parser.cpp.CPPNamespace;


public class ReflectionModelBuilder {

    public static final String CLASS_ANNOTATION = "Class";
    public static final String SIMPLE_NAME_PROPERTY = "simpleName";
    public static final String CANONICAL_NAME_PROPERTY = "canonicalName";

    private CppFileTuple cppFileTuple;


    public ReflectionModelBuilder() {

    }


    public ReflectionModel build(UpdaterContext updaterContext) {
        CPPFile headerCppFile = cppFileTuple.getHeaderCPPFile();
        CPPFile cppCppFile = cppFileTuple.getCppCPPFile();

        ReflectionModel model = new ReflectionModel();

        ClassModel classModel = null;
        if (headerCppFile != null) {
            for (CPPClassForwardDeclaration classForwardDeclaration : headerCppFile.getClassForwardDeclarations()) {
                String classForwardDeclarationName = classForwardDeclaration.getName();
                CPPNamespace namespace = classForwardDeclaration.getNamespace();
                String classForwardDeclarationNamespace = (namespace != null) ? namespace.getName() : null;
                String includeHeaderFilePath = ((classForwardDeclarationNamespace != null) ? (classForwardDeclarationNamespace.replace("::", "/") + "/") : "") + (classForwardDeclarationName + ".h");

                File includeHeaderFile = new File(updaterContext.getOriginalHeaderBaseDir(), includeHeaderFilePath);
                if (includeHeaderFile.exists() && includeHeaderFile.isFile()) {
                    model.addInclude(includeHeaderFilePath);
                    if (classForwardDeclarationNamespace != null) {
                        model.getUsingNamespaceDeclarations().add(classForwardDeclarationNamespace);
                    }
                }

            }

            model.addInclude(Utils.createRelativeHeaderFilePath(cppFileTuple));

            Map<String, ClassModel> classModelBySimpleName = new HashMap<String, ClassModel>();
            Map<String, String> classesDeclaredInClasses = new HashMap<String, String>();

            for (CPPClass classDeclaration : headerCppFile.getClasses()) {
                classModel = buildClassModel(updaterContext, classDeclaration, model.getIncludes());
                model.addClass(classModel);
                classModelBySimpleName.put(classModel.getClassName(), classModel);

                String declaredParentClassName = Utils.getDeclaredParentClassName(classDeclaration);
                if (declaredParentClassName != null) {
                    classesDeclaredInClasses.put(classModel.getClassName(), declaredParentClassName);
                }
            }

            for (Entry<String, String> entry : classesDeclaredInClasses.entrySet()) {
                String declaredClassName = entry.getKey();
                String declaredParentClassName = entry.getValue();

                classModelBySimpleName.get(declaredParentClassName).addDeclaredClass(declaredClassName);
                classModelBySimpleName.get(declaredClassName).setDeclaringClass(declaredParentClassName);
            }
        }

        if (cppCppFile != null) {
            for (CPPClass classDefinition : cppCppFile.getClasses()) {
                if (headerCppFile.getClass(classDefinition.getName()) == null) {
                    classModel = buildClassModel(updaterContext, classDefinition, model.getIncludes());
                    model.addClass(classModel);
                }
            }
        }

        return model;
    }

    public CppFileTuple getCppFileTuple() {
        return cppFileTuple;
    }

    public void setCppFileTuple(CppFileTuple cppFileTuple) {
        this.cppFileTuple = cppFileTuple;
    }

    protected static MethodModel buildMethodModel(CPPMethod method) {
        String returnType = method.getFunction().getType().toString().split("[(]")[0].trim();
        if (returnType.isEmpty()) {
            returnType = "void";
        }
        MethodModel methodModel = new MethodModel(method.getName(), returnType);
        if (method.getFunction().isStatic()) {
            methodModel.setStaticMethod(true);
        }
        switch (method.getVisibility()) {
        case PUBLIC: {
            methodModel.setPublicMethod(true);
        }
        case PRIVATE: {
            methodModel.setPrivateMethod(true);
        }
        case PROTECTED: {
            methodModel.setProtectedMethod(true);
        }
        default: {
            break;
        }
        }
        for (CPPMethodParameter param : method.getParameters()) {
            methodModel.addParameters(new ParameterModel(param.getName(), param.getType().getName()));
        }
        return methodModel;
    }

    protected static ClassModel buildClassModel(UpdaterContext updaterContext, CPPClass classDeclaration, Set<String> includes) {
        ClassModel classModel = new ClassModel(classDeclaration.getSimpleName());
        classModel.setAbstractClass(classDeclaration.isAbstractClass());

        CPPAnnotation annotation = classDeclaration.getAnnotation(CLASS_ANNOTATION);

        String simpleName = classDeclaration.getSimpleName();
        String canonicalName = classDeclaration.getName().replace("::", ".");

        if (annotation != null) {
            String value = annotation.getProperty(CANONICAL_NAME_PROPERTY);
            if (value != null) {
                canonicalName = value;
            }

            value = annotation.getProperty(SIMPLE_NAME_PROPERTY);
            if (value != null) {
                simpleName = value;
            }
        }
        classModel.setAnnotatedSimpleName(simpleName);
        classModel.setAnnotatedCanonicalName(canonicalName);

        classModel.setClassName(Utils.getClassName(classDeclaration));

        String namespaceName = classDeclaration.getNamespaceName();

        for (String nspace : namespaceName.split("::")) {
            classModel.addNamespaces(nspace);
        }

        for (CPPField field : classDeclaration.getFields()) {
            if (field.getName().equals("serialVersionUID")) {
                classModel.setSerialVersionUID(field.getField().getInitialValue().numericalValue());
            }
        }

        for (CPPField field : classDeclaration.getFields()) {
            FieldModel fieldModel = new FieldModel(field.getType().getName(), field.getName());
            classModel.addField(fieldModel);
            fieldModel.setStaticField(field.getType().isStatic());
            fieldModel.setConstField(field.isConst());
            switch (field.getVisibility()) {
            case PUBLIC: {
                fieldModel.setPublicField(true);
            }
            case PRIVATE: {
                fieldModel.setPrivateField(true);
            }
            case PROTECTED: {
                fieldModel.setProtectedField(true);
            }
            default: {
                break;
            }
            }
        }

        if (classDeclaration != null) {
            Map<String, Integer> methodNameCount = new HashMap<String, Integer>();
            for (CPPMethod method : classDeclaration.getMethods()) {
                MethodModel methodModel = buildMethodModel(method);

                Integer count = methodNameCount.get(method.getName());
                if (count == null) {
                    methodNameCount.put(method.getName(), 0);
                } else {
                    methodModel.setIndex(count.intValue() + 1);
                    methodNameCount.put(method.getName(), count.intValue() + 1);
                }

                if (method.isConstructor()) {
                    classModel.addConstructor(methodModel);
                } else {
                    classModel.addMethod(methodModel);
                }
            }
        }

        List<CPPBaseClass> baseClasses = classDeclaration.getBaseClasses();
        for (CPPBaseClass baseClass : baseClasses) {
            if (hasJObject(baseClass)) {
                String includeFilePath = createInclude(updaterContext.getOriginalHeaderBaseDir(), baseClass);
                if (includeFilePath != null) {
                    includes.add(includeFilePath);
                }
                classModel.setSuperClass(baseClass.getName());
            } else if (isInterface(baseClass)) {
                String includeFilePath = createInclude(updaterContext.getOriginalHeaderBaseDir(), baseClass);
                if (includeFilePath != null) {
                    includes.add(includeFilePath);
                }
                classModel.addInterface(baseClass.getName());
            }
        }

        return classModel;
    }

    protected static boolean isInterface(CPPBaseClass baseClass) {
        return hasJInterface(baseClass) && !hasJObject(baseClass);
    }

    protected static boolean hasJObject(CPPBaseClass baseClass) {
        if (baseClass.getName().equals("jcpp::lang::JObject")) {
            return true;
        }
        List<CPPBaseClass> baseClasses = baseClass.getBaseClasses();
        for (CPPBaseClass parentBaseClass : baseClasses) {
            if (hasJObject(parentBaseClass)) {
                return true;
            }
        }

        return false;
    }

    protected static boolean hasJInterface(CPPBaseClass baseClass) {
        if (baseClass.getName().equals("jcpp::lang::JInterface")) {
            return false;
        }
        List<CPPBaseClass> baseClasses = baseClass.getBaseClasses();
        for (CPPBaseClass parentBaseClass : baseClasses) {
            if (hasJInterface(parentBaseClass)) {
                return true;
            }
        }

        return false;
    }

    protected static String createInclude(File baseDir, CPPBaseClass baseClass) {
        String headerFilePath = baseClass.getName().replace("::", "/") + ".h";
        File headerFile = new File(baseDir, headerFilePath);
        return (headerFile.exists() && headerFile.isFile()) ? headerFilePath : null;
    }

}

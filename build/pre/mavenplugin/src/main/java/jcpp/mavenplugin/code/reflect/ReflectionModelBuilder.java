package jcpp.mavenplugin.code.reflect;

import java.io.File;

import java.util.HashMap;
import java.util.List;
import java.util.*;
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

    private static final String OBJECT_CLASS = "jcpp::lang::JObject";
    public static final String INTERFACE_CLASS = "jcpp::lang::JInterface";
    public static final String ENUM_CLASS = "jcpp::lang::JEnum";
    public static final String PROXY_CLASS = "jcpp::lang::reflect::JProxy";

    public static final String TRANSIENT_ANNOTATION = "Transient";
    public static final String IGNORE_REFLECTION_ANNOTATION = "IgnoreReflection";
    public static final String PRIMITIVE_ANNOTATION = "Primitive";
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
        Map<String, ClassModel> classModelBySimpleName = new TreeMap<String, ClassModel>();
        Map<String, ClassModel> classModelByCanName = new TreeMap<String, ClassModel>();
        Map<String, String> classesDeclaredInClasses = new TreeMap<String, String>();

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

            for (CPPClass classDeclaration : headerCppFile.getClasses()) {
                classModel = buildClassModel(updaterContext, classDeclaration, model.getIncludes());
                if (classModel != null) {
                    model.addClass(classModel);
                    classModelBySimpleName.put(classModel.getClassName(), classModel);
                    classModelByCanName.put(classModel.getAnnotatedCanonicalName(), classModel);

                    String declaredParentClassName = Utils.getDeclaredParentClassName(classModel);
                    if (declaredParentClassName != null) {
                        classesDeclaredInClasses.put(classModel.getAnnotatedCanonicalName(), declaredParentClassName);
                    }
                }
            }

            for (String entry : classesDeclaredInClasses.keySet()) {
                String declaredClassName = entry;
                ClassModel cm1=classModelByCanName.get(declaredClassName);
                String declaredParentClassName = classesDeclaredInClasses.get(declaredClassName);
                ClassModel cm2=classModelByCanName.get(declaredParentClassName);

                if (cm1!=null && cm2!=null){
                    cm2.addDeclaredClass(cm1.getClassName());
                    cm1.setDeclaringClass(cm2.getClassName());
                }
            }
        }

        if (cppCppFile != null) {
            for (CPPClass classDefinition : cppCppFile.getClasses()) {
                if ((headerCppFile == null) || (headerCppFile.getClass(classDefinition.getName()) == null)) {
                    classModel = buildClassModel(updaterContext, classDefinition, model.getIncludes());
                    if (classModel != null) {
                        model.addClass(classModel);
                        classModelBySimpleName.put(classModel.getClassName(), classModel);
                        classModelByCanName.put(classModel.getAnnotatedCanonicalName(), classModel);

                        String declaredParentClassName = Utils.getDeclaredParentClassName(classModel);
                        if (declaredParentClassName != null) {
                            classesDeclaredInClasses.put(classModel.getAnnotatedCanonicalName(), declaredParentClassName);
                        }
                    }
                }
            }

            for (String entry : classesDeclaredInClasses.keySet()) {
                String declaredClassName = entry;
                ClassModel cm1=classModelByCanName.get(declaredClassName);
                String declaredParentClassName = classesDeclaredInClasses.get(declaredClassName);
                ClassModel cm2=classModelByCanName.get(declaredParentClassName);

                if (cm1!=null && cm2!=null){
                    cm2.addDeclaredClass(cm1.getClassName());
                    cm1.setDeclaringClass(cm2.getClassName());
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
        CPPAnnotation ignoreReflectionAnnotation = method.getAnnotation(IGNORE_REFLECTION_ANNOTATION);
        if (ignoreReflectionAnnotation != null) {
            return null;
        }

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
        CPPAnnotation ignoreAnnotation = classDeclaration.getAnnotation(IGNORE_REFLECTION_ANNOTATION);
        if (ignoreAnnotation != null) {
            return null;
        }

        String simpleName = classDeclaration.getSimpleName();
        ClassModel classModel = new ClassModel(simpleName);
        classModel.setAbstractClass(classDeclaration.isAbstractClass());

        CPPAnnotation primitiveAnnotation = classDeclaration.getAnnotation(PRIMITIVE_ANNOTATION);
        if (primitiveAnnotation != null) {
            classModel.setPrimitive(true);
        }

        CPPAnnotation classAnnotation = classDeclaration.getAnnotation(CLASS_ANNOTATION);
        String canonicalName = classDeclaration.getName().replace("::", ".");

        if (classAnnotation != null) {
            String value = classAnnotation.getProperty(CANONICAL_NAME_PROPERTY);
            if (value != null) {
                canonicalName = value;
            }

            value = classAnnotation.getProperty(SIMPLE_NAME_PROPERTY);
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
            if (field.getName().equals("serialVersionUID") && field.isConst() && field.getType().isStatic()) {
                classModel.setSerialVersionUID(field.getField().getInitialValue().numericalValue());
            }

            CPPAnnotation ignoreReflectionAnnotation = field.getAnnotation(IGNORE_REFLECTION_ANNOTATION);
            if (ignoreReflectionAnnotation != null) {
                continue;
            }

            CPPAnnotation transientAnnotation = field.getAnnotation(TRANSIENT_ANNOTATION);
            
            FieldModel fieldModel = new FieldModel(field.getType().getName(), field.getName());
            classModel.addField(fieldModel);
            fieldModel.setStaticField(field.getType().isStatic());
            fieldModel.setConstField(field.isConst());
            fieldModel.setTransientField(transientAnnotation != null);
            
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
                if (methodModel == null) {
                    continue;
                }

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

        boolean isObject = false;
        boolean isInterface = false;
        boolean isEnum = false;
        boolean isProxy = false;

        List<CPPBaseClass> baseClasses = classDeclaration.getBaseClasses();
        for (CPPBaseClass baseClass : baseClasses) {
        	if(isProxy(baseClass)) {
        		isProxy = true;
        		classModel.setSuperClass(baseClass.getName());
        	} else if (isEnum(baseClass)) {
                isEnum = true;
                classModel.setSuperClass(baseClass.getName());
            } else if (isObject(baseClass)) {
                isObject = true;
                String includeFilePath = createInclude(updaterContext.getOriginalHeaderBaseDir(), baseClass);
                if (includeFilePath != null) {
                    includes.add(includeFilePath);
                }
                classModel.setSuperClass(baseClass.getName());
            } else if (isInterface(baseClass)) {
                isInterface = true;
                String includeFilePath = createInclude(updaterContext.getOriginalHeaderBaseDir(), baseClass);
                if (includeFilePath != null) {
                    includes.add(includeFilePath);
                }
                if (!baseClass.getName().equals(INTERFACE_CLASS)) {
                    classModel.addInterface(baseClass.getName());
                }
            }
        }

        if(isProxy) {
        	classModel.setProxyClass(true);
        } if (isEnum) {
            classModel.setEnumClass(true);
        } else if (isInterface && !isObject) {
            classModel.setInterfaceClass(true);
        }

        if (classModel.isEnumClass()) {
            for (FieldModel fieldModel : classModel.getFields()) {
                if (fieldModel.getStaticField() && fieldModel.getTypeClass().equals(classDeclaration.getName())) {
                    classModel.addEnumConstant(fieldModel.getName());
                }
            }
        }

        return classModel;
    }

    protected static boolean isObject(CPPBaseClass baseClass) {
        return hasClassInHierarchy(OBJECT_CLASS, baseClass);
    }

    protected static boolean isInterface(CPPBaseClass baseClass) {
        return hasClassInHierarchy(INTERFACE_CLASS, baseClass) && !hasClassInHierarchy(OBJECT_CLASS, baseClass);
    }

    protected static boolean isEnum(CPPBaseClass baseClass) {
        return hasClassInHierarchy(ENUM_CLASS, baseClass);
    }
    
    protected static boolean isProxy(CPPBaseClass baseClass) {
        return hasClassInHierarchy(PROXY_CLASS, baseClass);
    }

    protected static boolean hasClassInHierarchy(String className, CPPBaseClass baseClass) {
        if (baseClass.getName().equals(className)) {
            return true;
        }
        List<CPPBaseClass> baseClasses = baseClass.getBaseClasses();
        for (CPPBaseClass parentBaseClass : baseClasses) {
            if (hasClassInHierarchy(className, parentBaseClass)) {
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

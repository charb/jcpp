package jcpp.mavenplugin.code;

import java.io.File;
import java.io.IOException;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

import com.github.maven_nar.NarConstants;

import jcpp.parser.cpp.CPPClass;

import org.apache.maven.project.MavenProject;
import jcpp.mavenplugin.code.reflect.*;

public class Utils {

    private static final String FORWARD_SLASH = "/";
    private static final String DOUBLE_COLON = "::";
    private static final String CONST_PRIFIX = "const ";

    public static final String J_PRIMITIVE_VOID = "JPrimitiveVoid";
    public static final String J_PRIMITIVE_BOOLEAN = "JPrimitiveBoolean";
    public static final String J_PRIMITIVE_CHAR = "JPrimitiveChar";
    public static final String J_PRIMITIVE_DOUBLE = "JPrimitiveDouble";
    public static final String J_PRIMITIVE_FLOAT = "JPrimitiveFloat";
    public static final String J_PRIMITIVE_BYTE = "JPrimitiveByte";
    public static final String J_PRIMITIVE_LONG = "JPrimitiveLong";
    public static final String J_PRIMITIVE_SHORT = "JPrimitiveShort";

    private static final String JVOID = "void";
    private static final String JLONG1 = "long long";
    private static final String JLONG2 = "long long int";
    private static final String JLONG3 = "const long long int";
    private static final String JBOOL1 = "bool";
    private static final String JBOOL2 = "const bool";
    private static final String JCHAR1 = "unsigned short";
    private static final String JCHAR2 = "unsigned short int";
    private static final String JCHAR3 = "const unsigned short int";
    private static final String JBYTE1 = "char";
    private static final String JBYTE2 = "const char";
    private static final String JSHORT1 = "short";
    private static final String JSHORT2 = "short int";
    private static final String JSHORT3 = "const short int";
    private static final String JINT1 = "int";
    private static final String JINT2 = "const int";
    private static final String JDOUBLE1 = "double";
    private static final String JDOUBLE2 = "const double";
    private static final String JFLOAT1 = "float";
    private static final String JFLOAT2 = "const float";

    private static final String J_PRIMITIVE_INT = "JPrimitiveInt";

    public static final String DOT = ".";
    public static final Set<String> codeFileExtensions = new HashSet<String>(Arrays.asList("h", "hpp", "c", "cpp"));
    public static final Set<String> primitiveTypes = new HashSet<String>(Arrays.asList(JVOID, JINT1, JINT2, JSHORT1, JSHORT2, JSHORT3, JLONG1, JLONG2, JLONG3, JBYTE1, JBYTE2, JFLOAT1, JFLOAT2, JDOUBLE1, JDOUBLE2, JCHAR1,
            JCHAR2, JCHAR3, JBOOL1, JBOOL2));


    public Utils() {
    }


    public static String getCodeClassName(File codeFile) {
        String name = codeFile.getName();
        int index = name.lastIndexOf(DOT);
        return (index > 0) ? name.substring(0, index) : name;
    }

    public static boolean isCodeFile(File file) {
        String name = file.getName();
        int index = name.lastIndexOf(DOT);
        return (index > 0) ? codeFileExtensions.contains(name.substring(index + 1).toLowerCase()) : false;
    }

    public static String getNamespace(File codeFile, File baseDir) throws IOException {
        String fileRelativePath = codeFile.getCanonicalPath().substring(baseDir.getPath().length() + 1).replace("\\", FORWARD_SLASH).replace(FORWARD_SLASH, DOUBLE_COLON);
        int index = fileRelativePath.lastIndexOf(DOUBLE_COLON);
        return (index < 0) ? "" : fileRelativePath.substring(0, index);
    }

    public static String getFileRelativePath(File file, File baseDir) throws IOException {
        return file.getCanonicalPath().substring(baseDir.getPath().length() + 1).replace("\\", FORWARD_SLASH);
    }

    public static File getNoArchDirectory(File baseDir, MavenProject mp) {
        return new File(baseDir, mp.getArtifactId() + "-" + mp.getVersion() + "-" + NarConstants.NAR_NO_ARCH);
    }

    public static File getIncludeDirectory(File baseDir, MavenProject mp) {
        return new File(getNoArchDirectory(baseDir, mp), "include");
    }

    public static File getNoArchDirectory(File baseDir, String artifactId, String version) {
        return new File(baseDir, artifactId + "-" + version + "-" + NarConstants.NAR_NO_ARCH);
    }

    public static File getIncludeDirectory(File baseDir, String artifactId, String version) {
        return new File(getNoArchDirectory(baseDir, artifactId, version), "include");
    }

    public static boolean isDeclaredClass(CPPClass cppClass) {
        String namespaceName = cppClass.getNamespaceName();
        String fullName = ((namespaceName != null) && !namespaceName.isEmpty()) ? cppClass.getName().substring(namespaceName.length() + 2) : cppClass.getName();
        return fullName.indexOf(DOUBLE_COLON) > 0;
    }

    public static String getDeclaredParentSimpleClassName(CPPClass cppClass) {
        String namespaceName = cppClass.getNamespaceName();
        String fullName = ((namespaceName != null) && !namespaceName.isEmpty()) ? cppClass.getName().substring(namespaceName.length() + 2) : cppClass.getName();
        int index = fullName.lastIndexOf(DOUBLE_COLON);
        if (index < 0) {
            return null;
        }

        String parentFullName = fullName.substring(0, index);
        index = parentFullName.lastIndexOf(DOUBLE_COLON);

        return (index > 0) ? parentFullName.substring(index + 2) : parentFullName;
    }
    
    public static String getDeclaredParentClassName(ClassModel model) {
        int index = model.getAnnotatedCanonicalName().lastIndexOf("$");
        if (index < 0) {
            return null;
        }
        String parentFullName = model.getAnnotatedCanonicalName().substring(0, index);
        return parentFullName;
    }

    public static String getClassName(CPPClass cppClass) {
        String namespaceName = cppClass.getNamespaceName();
        return ((namespaceName != null) && !namespaceName.isEmpty()) ? cppClass.getName().substring(namespaceName.length() + 2) : cppClass.getName();
    }

    public static String createRelativeReflectionHeaderFilePath(CppFileTuple cppFileTuple) {
        StringBuilder pathBuilder = new StringBuilder();

        String namespace = cppFileTuple.getNamespace();
        if (namespace != null) {
            pathBuilder.append(namespace.replace(DOUBLE_COLON, FORWARD_SLASH)).append(FORWARD_SLASH);
        }
        pathBuilder.append(cppFileTuple.getName()).append("_Reflection.h");

        return pathBuilder.toString();
    }

    public static String createRelativeHeaderFilePath(CppFileTuple cppFileTuple) {
        StringBuilder pathBuilder = new StringBuilder();

        String namespace = cppFileTuple.getNamespace();
        if (namespace != null) {
            pathBuilder.append(namespace.replace(DOUBLE_COLON, FORWARD_SLASH)).append(FORWARD_SLASH);
        }
        pathBuilder.append(cppFileTuple.getName()).append(".h");

        return pathBuilder.toString();
    }

    // TODO update for JPrimitiveObjectArray::getClazz(TYPE::getClazz());
    public static String getTypeClass(String type) {
        String typeClass = type.replace("*", "").trim();
        typeClass = typeClass.startsWith(CONST_PRIFIX) ? typeClass.substring(6) : typeClass;
        if (typeClass.equals(JVOID)) {
            typeClass = J_PRIMITIVE_VOID;
        } else if (typeClass.equals(JINT1) || typeClass.equals(JINT2)) {
            typeClass = J_PRIMITIVE_INT;
        } else if (typeClass.equals(JSHORT1) || typeClass.equals(JSHORT2) || typeClass.equals(JSHORT3)) {
            typeClass = J_PRIMITIVE_SHORT;
        } else if (typeClass.equals(JLONG1) || typeClass.equals(JLONG2) || typeClass.equals(JLONG3)) {
            typeClass = J_PRIMITIVE_LONG;
        } else if (typeClass.equals(JBYTE1) || typeClass.equals(JBYTE2)) {
            typeClass = J_PRIMITIVE_BYTE;
        } else if (typeClass.equals(JFLOAT1) || typeClass.equals(JFLOAT2)) {
            typeClass = J_PRIMITIVE_FLOAT;
        } else if (typeClass.equals(JDOUBLE1) || typeClass.equals(JDOUBLE2)) {
            typeClass = J_PRIMITIVE_DOUBLE;
        } else if (typeClass.equals(JCHAR1) || typeClass.equals(JCHAR2) || typeClass.equals(JCHAR3)) {
            typeClass = J_PRIMITIVE_CHAR;
        } else if (typeClass.equals(JBOOL1) || typeClass.equals(JBOOL2)) {
            typeClass = J_PRIMITIVE_BOOLEAN;
        }
        return typeClass;
    }

    public static boolean isPrimitive(String type) {
        return primitiveTypes.contains(type);
    }

}

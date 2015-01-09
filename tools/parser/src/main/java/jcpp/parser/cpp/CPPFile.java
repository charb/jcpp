package jcpp.parser.cpp;

import java.io.File;
import java.io.InputStream;
import java.io.OutputStream;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

import javax.xml.bind.JAXBContext;
import javax.xml.bind.Marshaller;
import javax.xml.bind.Unmarshaller;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlElementWrapper;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

import org.eclipse.cdt.core.dom.ast.IASTTranslationUnit;


@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class CPPFile {

    private static JAXBContext context;


    static {
        try {
            context = JAXBContext.newInstance(CPPFile.class);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }


    @XmlTransient
    private String name;

    private String fileName;

    private Map<String, CPPNamespace> namespaces;

    private Map<String, CPPClass> classes;

    private List<CPPClassForwardDeclaration> classForwardDeclarations;

    @XmlElementWrapper(name = "globalVariables")
    @XmlElement(name = "globalVariable")
    private List<CPPVariable> globalVariables;

    private HashMap<String, CPPMethod> functions;

    @XmlTransient
    private IASTTranslationUnit translationUnit;


    public CPPFile() {
        namespaces = new LinkedHashMap<String, CPPNamespace>();
        classes = new HashMap<String, CPPClass>();
        classForwardDeclarations = new ArrayList<CPPClassForwardDeclaration>();
        globalVariables = new ArrayList<CPPVariable>();
        functions = new HashMap<String, CPPMethod>();
    }

    public CPPFile(String name) {
        this();
        this.name = name;
        this.fileName = new File(name).getName();
    }


    public static CPPFile readFrom(InputStream in) throws Exception {
        Unmarshaller unmarshaller = context.createUnmarshaller();
        return (CPPFile) unmarshaller.unmarshal(in);
    }

    public void writeTo(OutputStream out) throws Exception {
        Marshaller marshaller = context.createMarshaller();
        marshaller.setProperty(Marshaller.JAXB_FORMATTED_OUTPUT, true);
        marshaller.marshal(this, out);
    }

    public String getName() {
        return name;
    }

    public String getFileName() {
        return fileName;
    }

    public List<CPPVariable> getGlobalVariables() {
        return globalVariables;
    }

    public void addGlobalVariable(CPPVariable cppVariable) {
        globalVariables.add(cppVariable);
    }

    public CPPMethod[] getFunctions() {
        return functions.values().toArray(new CPPMethod[0]);
    }

    public void addFunction(CPPMethod function) {
        functions.put(function.getSignature(), function);
    }

    public CPPMethod getFunction(String signature) {
        return functions.get(signature);
    }

    public IASTTranslationUnit getTranslationUnit() {
        return translationUnit;
    }

    public void setTranslationUnit(IASTTranslationUnit translationUnit) {
        this.translationUnit = translationUnit;
    }

    public String getContent() {
        return translationUnit.getRawSignature();
    }

    public void addNamepsace(CPPNamespace cppNamespace) {
        namespaces.put(cppNamespace.getName(), cppNamespace);
    }

    public CPPNamespace getNamespace(String qualifiedName) {
        return namespaces.get(qualifiedName);
    }

    public CPPNamespace[] getNamespaces() {
        return namespaces.values().toArray(new CPPNamespace[0]);
    }

    public void addClass(CPPClass cppClass) {
        classes.put(cppClass.getName(), cppClass);
    }

    public CPPClass getClass(String name) {
        return classes.get(name);
    }

    public CPPClass[] getClasses() {
        return classes.values().toArray(new CPPClass[0]);
    }

    public void addClassForwardDeclaration(CPPClassForwardDeclaration classForwardDeclaration) {
        classForwardDeclarations.add(classForwardDeclaration);
    }

    public CPPClassForwardDeclaration[] getClassForwardDeclarations() {
        return classForwardDeclarations.toArray(new CPPClassForwardDeclaration[0]);
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("CPP File: name = ").append(name).append(" {").append(System.lineSeparator());
        sb.append("\tGlobal Variables:").append(System.lineSeparator());
        for (CPPVariable cppVariable : globalVariables) {
            sb.append('\t').append(cppVariable.toString()).append(System.lineSeparator());
        }
        sb.append("\tFunctions:").append(System.lineSeparator());
        for (CPPMethod cppMethod : functions.values()) {
            sb.append('\t').append(cppMethod.toString());
        }
        sb.append("\tClasses:").append(System.lineSeparator());
        for (CPPClass cppClass : classes.values()) {
            sb.append('\t').append(cppClass.toString());
        }
        sb.append('}').append(System.lineSeparator());
        return sb.toString();
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = (prime * result) + ((fileName == null) ? 0 : fileName.hashCode());
        result = (prime * result) + ((namespaces == null) ? 0 : namespaces.hashCode());
        result = (prime * result) + ((classes == null) ? 0 : classes.hashCode());
        result = (prime * result) + ((classForwardDeclarations == null) ? 0 : classForwardDeclarations.hashCode());
        result = (prime * result) + ((functions == null) ? 0 : functions.hashCode());
        result = (prime * result) + ((globalVariables == null) ? 0 : globalVariables.hashCode());
        return result;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (obj == null) {
            return false;
        }
        if (!(obj instanceof CPPFile)) {
            return false;
        }
        CPPFile other = (CPPFile) obj;
        if (fileName == null) {
            if (other.fileName != null) {
                return false;
            }
        } else if (!fileName.equals(other.fileName)) {
            return false;
        }
        if (namespaces == null) {
            if (other.namespaces != null) {
                return false;
            }
        } else if (!namespaces.equals(other.namespaces)) {
            return false;
        }
        if (classes == null) {
            if (other.classes != null) {
                return false;
            }
        } else if (!classes.equals(other.classes)) {
            return false;
        }
        if (classForwardDeclarations == null) {
            if (other.classForwardDeclarations != null) {
                return false;
            }
        } else if (!classForwardDeclarations.equals(other.classForwardDeclarations)) {
            return false;
        }
        if (functions == null) {
            if (other.functions != null) {
                return false;
            }
        } else if (!functions.equals(other.functions)) {
            return false;
        }
        if (globalVariables == null) {
            if (other.globalVariables != null) {
                return false;
            }
        } else if (!globalVariables.equals(other.globalVariables)) {
            return false;
        }
        return true;
    }

}

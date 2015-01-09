package jcpp.parser.cpp;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlElementWrapper;
import javax.xml.bind.annotation.XmlID;
import javax.xml.bind.annotation.XmlIDREF;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

import org.eclipse.cdt.core.dom.ast.IASTComment;
import org.eclipse.cdt.core.dom.ast.IASTNode;
import org.eclipse.cdt.core.dom.ast.IBinding;
import org.eclipse.cdt.core.dom.ast.IType;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPASTCompositeTypeSpecifier;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPASTCompositeTypeSpecifier.ICPPASTBaseSpecifier;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPBase;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPClassType;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPMethod;


@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class CPPClass {

    @XmlIDREF
    private CPPNamespace namespace;

    @XmlID
    private String name;

    private String namespaceName;

    private String simpleName;

    @XmlTransient //xmlTransient until this is added to the hashcode and equals methods + unit test resources updated.
    private boolean abstractClass;

    @XmlElement(name = "field")
    @XmlElementWrapper(name = "fields")
    private List<CPPField> fields;

    private HashMap<String, CPPMethod> methods;

    @XmlElement(name = "baseClass")
    @XmlElementWrapper(name = "baseClasses")
    private List<CPPBaseClass> baseClasses;

    @XmlElement(name = "annotation")
    @XmlElementWrapper(name = "annotations")
    private List<CPPAnnotation> annotations;

    @XmlTransient
    private ICPPASTCompositeTypeSpecifier compositeTypeSpecifier;


    public CPPClass() {
        this.fields = new ArrayList<CPPField>();
        this.methods = new HashMap<String, CPPMethod>();
        this.baseClasses = new ArrayList<CPPBaseClass>();
        this.annotations = new ArrayList<CPPAnnotation>();
    }

    public CPPClass(String name, CPPNamespace namespace) {
        this();
        this.name = name;
        this.namespace = namespace;
        if (this.namespace != null) {
            this.namespaceName = namespace.getName();
            this.simpleName = name.substring(name.lastIndexOf("::") + 2);
        } else {
            this.namespaceName = "";
            this.simpleName = (name.lastIndexOf("::") > -1) ? name.substring(name.lastIndexOf("::") + 2) : name;
        }
    }


    public CPPNamespace getNamespace() {
        return namespace;
    }

    public String getName() {
        return name;
    }

    public String getNamespaceName() {
        return namespaceName;
    }

    public String getSimpleName() {
        return simpleName;
    }

    public boolean isAbstractClass() {
        return abstractClass;
    }

    public void addField(CPPField field) {
        field.setCppClass(this);
        fields.add(field);
    }

    public List<CPPField> getFields() {
        return fields;
    }

    public void addMethod(CPPMethod cppMethod) {
        cppMethod.setCppClass(this);
        methods.put(cppMethod.getSignature(), cppMethod);
    }

    public CPPMethod getMethod(String signature) {
        return methods.get(signature);
    }

    public CPPMethod[] getMethods() {
        return methods.values().toArray(new CPPMethod[0]);
    }

    public List<CPPBaseClass> getBaseClasses() {
        return baseClasses;
    }

    public List<CPPAnnotation> getAnnotations() {
        return annotations;
    }

    public CPPAnnotation getAnnotation(String name) {
        for (CPPAnnotation annotation : annotations) {
            if (annotation.getName().equals(name)) {
                return annotation;
            }
        }
        return null;
    }

    public ICPPASTCompositeTypeSpecifier getCompositeTypeSpecifier() {
        return compositeTypeSpecifier;
    }

    public void setCompositeTypeSpecifier(ICPPASTCompositeTypeSpecifier compositeTypeSpecifier) {
        if (this.compositeTypeSpecifier == null) {
            this.compositeTypeSpecifier = compositeTypeSpecifier;
            initBaseClasses();
            initAnnotations();
            checkIfAbstract();
        } else if (!this.compositeTypeSpecifier.equals(compositeTypeSpecifier)) {
            throw new IllegalArgumentException("Cannot change the AST type specifier of class " + this.name + ". New type specifier: " + compositeTypeSpecifier.getName());
        }
    }

    @Override
    public String toString() {
        String str = "Class:  name=" + name + "\r\n";
        for (CPPField f : fields) {
            str += "		" + f + "\r\n";
        }
        str += "\r\n\r\n";
        for (CPPMethod m : methods.values()) {
            str += "		" + m + "\r\n";
        }
        return str;
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = (prime * result) + ((name == null) ? 0 : name.hashCode());
        result = (prime * result) + ((namespaceName == null) ? 0 : namespaceName.hashCode());
        result = (prime * result) + ((simpleName == null) ? 0 : simpleName.hashCode());
        result = (prime * result) + ((fields == null) ? 0 : fields.hashCode());
        result = (prime * result) + ((methods == null) ? 0 : methods.hashCode());
        result = (prime * result) + ((baseClasses == null) ? 0 : baseClasses.hashCode());
        result = (prime * result) + ((annotations == null) ? 0 : annotations.hashCode());
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
        if (!(obj instanceof CPPClass)) {
            return false;
        }
        CPPClass other = (CPPClass) obj;
        if (name == null) {
            if (other.name != null) {
                return false;
            }
        } else if (!name.equals(other.name)) {
            return false;
        }
        if (namespaceName == null) {
            if (other.namespaceName != null) {
                return false;
            }
        } else if (!namespaceName.equals(other.namespaceName)) {
            return false;
        }
        if (simpleName == null) {
            if (other.simpleName != null) {
                return false;
            }
        } else if (!simpleName.equals(other.simpleName)) {
            return false;
        }
        if (fields == null) {
            if (other.fields != null) {
                return false;
            }
        } else if (!fields.equals(other.fields)) {
            return false;
        }
        if (methods == null) {
            if (other.methods != null) {
                return false;
            }
        } else if (!methods.equals(other.methods)) {
            return false;
        }
        if (baseClasses == null) {
            if (other.baseClasses != null) {
                return false;
            }
        } else if (!baseClasses.equals(other.baseClasses)) {
            return false;
        }
        if (annotations == null) {
            if (other.annotations != null) {
                return false;
            }
        } else if (!annotations.equals(other.annotations)) {
            return false;
        }
        return true;
    }

    private void initBaseClasses() {
        ICPPASTBaseSpecifier[] baseSpecifiers = compositeTypeSpecifier.getBaseSpecifiers();
        for (ICPPASTBaseSpecifier baseSpecifier : baseSpecifiers) {
            this.baseClasses.add(new CPPBaseClass(baseSpecifier));
        }
    }

    private void initAnnotations() {
        IASTNode parent = compositeTypeSpecifier.getParent();
        IASTNode grandParent = parent.getParent();
        int startCommentOffset = 0;
        int endCommentOffset = parent.getFileLocation().getNodeOffset();
        IASTNode[] children = grandParent.getChildren();
        int i = 0;
        while (children[i] != parent) {
            i++;
        }
        if ((i - 1) >= 0) {
            startCommentOffset = children[i - 1].getFileLocation().getNodeOffset() + children[i - 1].getFileLocation().getNodeLength();
        }
        String fileName = compositeTypeSpecifier.getFileLocation().getFileName();
        for (IASTComment astComment : grandParent.getTranslationUnit().getComments()) {
            if (astComment.getFileLocation().getFileName().equals(fileName)) {
                int commentOffset = astComment.getFileLocation().getNodeOffset();
                if ((commentOffset > startCommentOffset) && (commentOffset < endCommentOffset)) {
                    this.annotations.addAll(CPPAnnotation.parseAnnotations(astComment));
                }
            }
        }
    }

    private void checkIfAbstract() {
        IBinding binding = compositeTypeSpecifier.getName().getBinding();
        if (binding instanceof ICPPClassType) {
            Set<String> signatures = new HashSet<String>();
            collectPureVirtualMethods((ICPPClassType) binding, signatures, new HashSet<String>(), new HashSet<String>());
            abstractClass = signatures.size() > 0;
        }
    }

    private void collectPureVirtualMethods(ICPPClassType classType, Set<String> signatures, Set<String> signaturesRemoved, Set<String> classesVisited) {
        String className = classType.getName();
        if (classesVisited.contains(className)) {
            return;
        }
        classesVisited.add(className);
        ICPPBase[] bases = classType.getBases();
        if (bases != null) {
            for (ICPPBase base : bases) {
                IType type = base.getBaseClassType();
                if (type instanceof ICPPClassType) {
                    ICPPClassType baseClassType = (ICPPClassType) type;
                    collectPureVirtualMethods(baseClassType, signatures, signaturesRemoved, classesVisited);
                }
            }
        }
        ICPPMethod[] classMethods = classType.getMethods();
        if (classMethods != null) {
            for (ICPPMethod classMethod : classMethods) {
                String signature = classMethod.toString();
                if (!signaturesRemoved.contains(signature)) {
                    if (classMethod.isPureVirtual()) {
                        signatures.add(signature);
                    } else if (signatures.contains(signature)) {
                        signaturesRemoved.add(signature);
                        signatures.remove(signature);
                    }
                }
            }
        }
    }

}

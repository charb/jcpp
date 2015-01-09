package jcpp.parser.cpp;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlID;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

import org.eclipse.cdt.core.dom.ast.cpp.ICPPASTNamespaceDefinition;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class CPPNamespace {

    @XmlID
    private String name;

    private String lastName;

    @XmlTransient
    private ICPPASTNamespaceDefinition namespaceDefinition;

    @XmlTransient
    private org.eclipse.cdt.internal.core.dom.parser.cpp.CPPNamespace namespace;

    public CPPNamespace() {
    }

    public CPPNamespace(ICPPASTNamespaceDefinition namespaceDefinition) {
        this.namespaceDefinition = namespaceDefinition;
        this.namespace = (org.eclipse.cdt.internal.core.dom.parser.cpp.CPPNamespace) this.namespaceDefinition.getName().getBinding();
        if (this.namespace == null) {
            this.namespace = (org.eclipse.cdt.internal.core.dom.parser.cpp.CPPNamespace) this.namespaceDefinition.getName().resolveBinding();
        }
        this.name = this.namespace.toString();
        this.lastName = this.namespace.getName();
    }

    public String getName() {
        return name;
    }

    public String getLastName() {
        return lastName;
    }

    public String[] getQualifiedName() {
        return this.namespace.getQualifiedName();
    }
    
    public ICPPASTNamespaceDefinition getNamespaceDefinition() {
        return namespaceDefinition;
    }

    public org.eclipse.cdt.internal.core.dom.parser.cpp.CPPNamespace getNamespace() {
        return namespace;
    }

    @Override
    public String toString() {
        return getClass().getSimpleName() + " [name: " + name + "]";
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = prime * result + ((name == null) ? 0 : name.hashCode());
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
        if (!(obj instanceof CPPNamespace)) {
            return false;
        }
        CPPNamespace other = (CPPNamespace) obj;
        if (name == null) {
            if (other.name != null) {
                return false;
            }
        } else if (!name.equals(other.name)) {
            return false;
        }
        return true;
    }

}

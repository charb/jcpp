package jcpp.parser.cpp;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlIDREF;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

import org.eclipse.cdt.core.dom.ast.cpp.ICPPASTElaboratedTypeSpecifier;


@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class CPPClassForwardDeclaration {

    private String name;

    @XmlIDREF
    private CPPNamespace namespace;

    @XmlTransient
    private ICPPASTElaboratedTypeSpecifier elaboratedTypeSpecifier;

    public CPPClassForwardDeclaration() {
    }

    public CPPClassForwardDeclaration(ICPPASTElaboratedTypeSpecifier elaboratedTypeSpecifier, CPPNamespace namespace) {
        super();
        this.elaboratedTypeSpecifier = elaboratedTypeSpecifier;
        this.namespace = namespace;
        this.name = this.elaboratedTypeSpecifier.getName().toString();
    }

    public String getName() {
        return name;
    }

    public CPPNamespace getNamespace() {
        return namespace;
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = prime * result + ((name == null) ? 0 : name.hashCode());
        result = prime * result + ((namespace == null) ? 0 : namespace.hashCode());
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
        if (!(obj instanceof CPPClassForwardDeclaration)) {
            return false;
        }
        CPPClassForwardDeclaration other = (CPPClassForwardDeclaration) obj;
        if (name == null) {
            if (other.name != null) {
                return false;
            }
        } else if (!name.equals(other.name)) {
            return false;
        }
        if (namespace == null) {
            if (other.namespace != null) {
                return false;
            }
        } else if (!namespace.equals(other.namespace)) {
            return false;
        }
        return true;
    }

}

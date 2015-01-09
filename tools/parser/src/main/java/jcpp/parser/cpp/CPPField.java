package jcpp.parser.cpp;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlIDREF;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

import org.eclipse.cdt.core.dom.ast.IASTSimpleDeclaration;
import org.eclipse.cdt.core.dom.ast.IField;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPMember;


@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class CPPField {

    private String name;

    private CPPType type;

    private CPPVisibilityLabel visibility;

    @XmlIDREF
    private CPPClass cppClass;

    @XmlTransient
    private IASTSimpleDeclaration simpleDeclaration;

    @XmlTransient
    private IField field;


    public CPPField() {
    }

    public CPPField(IASTSimpleDeclaration simpleDeclaration, IField field) {
        this.simpleDeclaration = simpleDeclaration;
        this.field = field;
        this.name = field.getName();
        this.type = new CPPType(field);
        this.visibility = (field instanceof ICPPMember) ? CPPVisibilityLabel.getVisibilityLabel(((ICPPMember) field).getVisibility()) : CPPVisibilityLabel.UNKNOWN;
    }


    public boolean isConst() {
        return (simpleDeclaration != null) && (simpleDeclaration.getDeclSpecifier() != null) && simpleDeclaration.getDeclSpecifier().isConst();
    }

    public String getName() {
        return name;
    }

    public CPPType getType() {
        return type;
    }

    public CPPVisibilityLabel getVisibility() {
        return visibility;
    }

    public CPPClass getCppClass() {
        return cppClass;
    }

    public void setCppClass(CPPClass cppClass) {
        this.cppClass = cppClass;
    }

    public IASTSimpleDeclaration getSimpleDeclaration() {
        return simpleDeclaration;
    }

    public IField getField() {
        return field;
    }

    @Override
    public String toString() {
        return getClass().getSimpleName() + " [name: " + name + "][type: " + type + "][visibility: " + visibility + "]";
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = (prime * result) + ((name == null) ? 0 : name.hashCode());
        result = (prime * result) + ((type == null) ? 0 : type.hashCode());
        result = (prime * result) + ((visibility == null) ? 0 : visibility.hashCode());
        result = (prime * result) + ((cppClass == null) ? 0 : cppClass.getName().hashCode());
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
        if (!(obj instanceof CPPField)) {
            return false;
        }
        CPPField other = (CPPField) obj;
        if (name == null) {
            if (other.name != null) {
                return false;
            }
        } else if (!name.equals(other.name)) {
            return false;
        }
        if (type == null) {
            if (other.type != null) {
                return false;
            }
        } else if (!type.equals(other.type)) {
            return false;
        }
        if (visibility != other.visibility) {
            return false;
        }
        if (cppClass == null) {
            if (other.cppClass != null) {
                return false;
            }
        } else if (!cppClass.getName().equals(other.cppClass.getName())) {
            return false;
        }
        return true;
    }

}

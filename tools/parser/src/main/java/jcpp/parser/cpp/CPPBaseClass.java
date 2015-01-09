package jcpp.parser.cpp;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlElementWrapper;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

import org.eclipse.cdt.core.dom.ast.cpp.ICPPASTCompositeTypeSpecifier.ICPPASTBaseSpecifier;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPBase;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPClassType;
import org.eclipse.cdt.internal.core.dom.parser.ProblemBinding;
import org.eclipse.cdt.internal.core.dom.parser.cpp.CPPBaseClause;
import org.eclipse.cdt.internal.core.dom.parser.cpp.semantics.CPPVisitor;


@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class CPPBaseClass {

    @XmlAttribute
    private String name; //qualified

    @XmlAttribute
    private boolean virtual;

    @XmlAttribute
    private CPPVisibilityLabel visibility;

    @XmlElement(name = "baseClass")
    private List<CPPBaseClass> baseClasses;

    @XmlTransient
    private ICPPASTBaseSpecifier baseSpecifier;

    @XmlTransient
    private ICPPBase cppBase;

    @XmlTransient
    private ICPPClassType cppClassType;


    public CPPBaseClass() {
    }

    public CPPBaseClass(ICPPBase cppBase) {
        this.cppBase = cppBase;
        this.cppClassType = (ICPPClassType) this.cppBase.getBaseClassType();
        if (cppClassType instanceof ProblemBinding) {
            ProblemBinding problemBinding = (ProblemBinding) cppClassType;
            throw new IllegalStateException(problemBinding.getName() + " - " + problemBinding.getMessage() + " @ " + problemBinding.getFileName() + " : " + problemBinding.getLineNumber());
        }
        String[] qName = CPPVisitor.getQualifiedName(cppClassType);
        this.name = qName[0];
        for (int i = 1; i < qName.length; i++) {
            this.name += "::" + qName[i];
        }
        this.virtual = this.cppBase.isVirtual();
        this.visibility = CPPVisibilityLabel.getVisibilityLabel(this.cppBase.getVisibility());
        ICPPBase[] bases = cppClassType.getBases();
        this.baseClasses = bases.length > 0 ? new ArrayList<CPPBaseClass>(bases.length) : null;
        for (ICPPBase base : bases) {
            this.baseClasses.add(new CPPBaseClass(base)); //TODO: cache the CPPBaseClass object by the qualified name?
        }
    }

    public CPPBaseClass(ICPPASTBaseSpecifier baseSpecifier) {
        this(new CPPBaseClause(baseSpecifier));
        this.baseSpecifier = baseSpecifier;
    }


    public String getName() {
        return name;
    }

    public boolean isVirtual() {
        return virtual;
    }

    public CPPVisibilityLabel getVisibility() {
        return visibility;
    }

    public List<CPPBaseClass> getBaseClasses() {
        if (baseClasses == null) {
            baseClasses = Collections.<CPPBaseClass>emptyList();
        }
        return baseClasses;
    }

    public ICPPASTBaseSpecifier getBaseSpecifier() {
        return baseSpecifier;
    }

    public ICPPBase getCppBase() {
        return cppBase;
    }

    @Override
    public String toString() {
        return getClass().getSimpleName() + " [name: " + name + "][virtual: " + virtual + "][visibility: " + visibility + "]";
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = (prime * result) + ((name == null) ? 0 : name.hashCode());
        result = (prime * result) + (virtual ? 1231 : 1237);
        result = (prime * result) + ((visibility == null) ? 0 : visibility.hashCode());
        result = (prime * result) + ((baseClasses == null) ? 0 : baseClasses.hashCode());
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
        if (!(obj instanceof CPPBaseClass)) {
            return false;
        }
        CPPBaseClass other = (CPPBaseClass) obj;
        if (name == null) {
            if (other.name != null) {
                return false;
            }
        } else if (!name.equals(other.name)) {
            return false;
        }
        if (virtual != other.virtual) {
            return false;
        }
        if (visibility != other.visibility) {
            return false;
        }
        if (baseClasses == null) {
            if (other.baseClasses != null) {
                return false;
            }
        } else if (!baseClasses.equals(other.baseClasses)) {
            return false;
        }
        return true;
    }

}

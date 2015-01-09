package jcpp.parser.cpp;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

import org.eclipse.cdt.core.dom.ast.ASTTypeUtil;
import org.eclipse.cdt.core.dom.ast.IPointerType;
import org.eclipse.cdt.core.dom.ast.IType;
import org.eclipse.cdt.core.dom.ast.IVariable;


@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class CPPType {

    @XmlAttribute
    private String name;

    @XmlAttribute
    private String typetype;

    @XmlAttribute
    private boolean isStatic;

    @XmlAttribute
    private boolean isPointer;

    @XmlTransient
    private IType type;


    public CPPType() {
    }

    public CPPType(IVariable variable) {
        this.type = variable.getType();
        this.name = ASTTypeUtil.getType(this.type);
        this.isPointer = this.type instanceof IPointerType;
        this.isStatic = variable.isStatic();
        this.typetype = this.type.getClass().getName();
    }


    public String getName() {
        return name;
    }

    public boolean isStatic() {
        return isStatic;
    }

    public boolean isPointer() {
        return isPointer;
    }

    public IType getType() {
        return type;
    }

    @Override
    public String toString() {
        return getClass().getName() + " [name: " + name + "][typetype: " + typetype + "][isStatic: " + isStatic + "][isPointer: " + isPointer + "]";
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = (prime * result) + (isPointer ? 1231 : 1237);
        result = (prime * result) + (isStatic ? 1231 : 1237);
        result = (prime * result) + ((name == null) ? 0 : name.hashCode());
        result = (prime * result) + ((typetype == null) ? 0 : typetype.hashCode());
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
        if (!(obj instanceof CPPType)) {
            return false;
        }
        CPPType other = (CPPType) obj;
        if (isPointer != other.isPointer) {
            return false;
        }
        if (isStatic != other.isStatic) {
            return false;
        }
        if (name == null) {
            if (other.name != null) {
                return false;
            }
        } else if (!name.equals(other.name)) {
            return false;
        }
        if (typetype == null) {
            if (other.typetype != null) {
                return false;
            }
        } else if (!typetype.equals(other.typetype)) {
            return false;
        }
        return true;
    }

}

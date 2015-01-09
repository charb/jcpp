package jcpp.parser.cpp;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

import org.eclipse.cdt.core.dom.ast.IASTName;
import org.eclipse.cdt.core.dom.ast.IASTParameterDeclaration;
import org.eclipse.cdt.core.dom.ast.IParameter;


@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class CPPMethodParameter {

    private String name;

    private CPPType type;

    @XmlTransient
    private IASTParameterDeclaration parameterDeclaration;

    @XmlTransient
    private IASTName astName; //.getBinding() returns the IParameter/ICPPParameter //TODO: do we need this field? we can get it with parameterDeclaration.getDeclarator().getName()

    @XmlTransient
    private IParameter parameter;


    public CPPMethodParameter() {
    }

    public CPPMethodParameter(IASTParameterDeclaration parameterDeclaration) {
        this.parameterDeclaration = parameterDeclaration;
        this.astName = parameterDeclaration.getDeclarator().getName();
        this.parameter = (IParameter) this.astName.getBinding();
        if (this.parameter == null) {
            this.parameter = (IParameter) this.astName.resolveBinding();
        }
        this.name = this.parameter.getName();
        this.type = new CPPType(parameter);
    }


    public String getName() {
        return name;
    }

    public CPPType getType() {
        return type;
    }

    public IASTParameterDeclaration getParameterDeclaration() {
        return parameterDeclaration;
    }

    public IASTName getAstName() {
        return astName;
    }

    public IParameter getParameter() {
        return parameter;
    }

    @Override
    public String toString() {
        return getClass().getSimpleName() + " [name: " + name + "][type: " + type + "]";
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = (prime * result) + ((name == null) ? 0 : name.hashCode());
        result = (prime * result) + ((type == null) ? 0 : type.hashCode());
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
        if (!(obj instanceof CPPMethodParameter)) {
            return false;
        }
        CPPMethodParameter other = (CPPMethodParameter) obj;
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
        return true;
    }

}

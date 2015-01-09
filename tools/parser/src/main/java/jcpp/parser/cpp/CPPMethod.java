package jcpp.parser.cpp;

import java.util.ArrayList;
import java.util.List;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlElementWrapper;
import javax.xml.bind.annotation.XmlIDREF;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

import org.eclipse.cdt.core.dom.ast.IASTFunctionDeclarator;
import org.eclipse.cdt.core.dom.ast.IASTFunctionDefinition;
import org.eclipse.cdt.core.dom.ast.IASTName;
import org.eclipse.cdt.core.dom.ast.IASTParameterDeclaration;
import org.eclipse.cdt.core.dom.ast.IASTStandardFunctionDeclarator;
import org.eclipse.cdt.core.dom.ast.IFunction;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPConstructor;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPMember;


@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class CPPMethod { //TODO: add file location in toString() ?

    private String name;

    private String signature;

    private CPPVisibilityLabel visibility;

    private boolean constructor;

    @XmlElement(name = "parameter")
    @XmlElementWrapper(name = "parameters")
    private List<CPPMethodParameter> parameters;

    @XmlElement(name = "variable")
    @XmlElementWrapper(name = "variables")
    private List<CPPVariable> variables;

    @XmlIDREF
    private CPPClass cppClass;

    @XmlTransient
    private IASTName astName;

    //NOTE use ((org.eclipse.cdt.core.dom.ast.IASTFunctionDefinition) functionDefinition).getBody() to find where to insert new statements at start of function body.
    @XmlTransient
    private IASTFunctionDefinition functionDefinition;

    @XmlTransient
    private  IASTFunctionDeclarator functionDeclarator;

    @XmlTransient
    private IFunction function;


    public CPPMethod() {
        this.parameters = new ArrayList<CPPMethodParameter>();
        this.variables = new ArrayList<CPPVariable>();
    }

    public CPPMethod(IASTFunctionDefinition functionDefinition) {
        this(functionDefinition.getDeclarator());
        this.functionDefinition = functionDefinition;
    }

    public CPPMethod(IASTFunctionDeclarator functionDeclarator) {
        this();
        this.functionDeclarator = functionDeclarator;
        this.astName = this.functionDeclarator.getName();
        this.function = (IFunction) this.astName.getBinding();
        if (this.function == null) {
            try {
                this.function = (IFunction) this.astName.resolveBinding();
            } catch (Exception e) {
                e.printStackTrace();
            }

        }
        this.constructor = function instanceof ICPPConstructor;
        this.signature = this.function.toString();
        this.name = this.function.getName();
        this.visibility = (function instanceof ICPPMember) ? CPPVisibilityLabel.getVisibilityLabel(((ICPPMember) function).getVisibility()) : CPPVisibilityLabel.UNKNOWN;

        if (this.functionDeclarator instanceof IASTStandardFunctionDeclarator) {
            IASTStandardFunctionDeclarator standardfunctionDeclarator = (IASTStandardFunctionDeclarator) this.functionDeclarator;
            IASTParameterDeclaration[] params = standardfunctionDeclarator.getParameters();
            for (IASTParameterDeclaration param : params) {
                this.parameters.add(new CPPMethodParameter(param));
            }
        } else {
            throw new IllegalArgumentException("Unkown function definition: " + this.functionDeclarator);
            //TODO: what about ICASTKnRFunctionDeclarator (see subinterfaces of IASTFunctionDeclarator)
        }

//      below is another way of getting the parameters from the IParameter "CDT semantic" interface
//        IParameter[] parameters = this.function.getParameters();
//        for (IParameter parameter : parameters) {
////            this.parameters.add(new CPPMethodParameter((IASTName) ((ICPPInternalBinding) parameter).getDefinition()));
//            this.parameters.add(new CPPMethodParameter(parameter)); //TODO: how to find if parameter is a pointer, just from IParameter?
//        }
    }


    public boolean isConstructor() {
        return constructor;
    }

    public void setConstructor(boolean constructor) {
        this.constructor = constructor;
    }

    public String getName() {
        return name;
    }

    public String getSignature() {
        return signature;
    }

    public CPPVisibilityLabel getVisibility() {
        return visibility;
    }

    public List<CPPMethodParameter> getParameters() {
        return parameters;
    }

    public List<CPPVariable> getVariables() {
        return variables;
    }

    public void addVariable(CPPVariable cppVariable) {
        variables.add(cppVariable);
    }

    public CPPClass getCppClass() {
        return cppClass;
    }

    public void setCppClass(CPPClass cppClass) {
        this.cppClass = cppClass;
    }

    public IASTName getAstName() {
        return astName;
    }

    public IASTFunctionDefinition getFunctionDefinition() {
        return functionDefinition;
    }

    public IASTFunctionDeclarator getFunctionDeclarator() {
        return functionDeclarator;
    }

    public IFunction getFunction() {
        return function;
    }

    public boolean isFunctionDefinition() {
        return functionDefinition != null;
    }

    @Override
    public String toString() {
        return getClass().getSimpleName() + " [name: " + name + "][signature: " + signature + "][visiblity: " + visibility + "][parameters: " + parameters + "][variables: " + variables + "]";
    }

    public String prettyPrint() {
        StringBuffer sb = new StringBuffer();
        sb.append(name).append('(').append(parameters.toString()).append(") {\r\n");
        for (CPPVariable v : variables) {
            sb.append('\t').append(v.toString()).append("\r\n");
        }
        sb.append("}\r\n");
        return sb.toString();
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = (prime * result) + ((name == null) ? 0 : name.hashCode());
        result = (prime * result) + ((signature == null) ? 0 : signature.hashCode());
        result = (prime * result) + ((visibility == null) ? 0 : visibility.hashCode());
        result = (prime * result) + (constructor ? 1231 : 1237);
        result = (prime * result) + ((cppClass == null) ? 0 : cppClass.getName().hashCode());
        result = (prime * result) + ((parameters == null) ? 0 : parameters.hashCode());
        result = (prime * result) + ((variables == null) ? 0 : variables.hashCode());
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
        if (!(obj instanceof CPPMethod)) {
            return false;
        }
        CPPMethod other = (CPPMethod) obj;
        if (name == null) {
            if (other.name != null) {
                return false;
            }
        } else if (!name.equals(other.name)) {
            return false;
        }
        if (signature == null) {
            if (other.signature != null) {
                return false;
            }
        } else if (!signature.equals(other.signature)) {
            return false;
        }
        if (visibility != other.visibility) {
            return false;
        }
        if (constructor != other.constructor) {
            return false;
        }
        if (cppClass == null) {
            if (other.cppClass != null) {
                return false;
            }
        } else if (!cppClass.getName().equals(other.cppClass.getName())) {
            return false;
        }
        if (parameters == null) {
            if (other.parameters != null) {
                return false;
            }
        } else if (!parameters.equals(other.parameters)) {
            return false;
        }
        if (variables == null) {
            if (other.variables != null) {
                return false;
            }
        } else if (!variables.equals(other.variables)) {
            return false;
        }
        return true;
    }

}

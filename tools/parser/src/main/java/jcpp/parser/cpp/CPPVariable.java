package jcpp.parser.cpp;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

import org.eclipse.cdt.core.dom.ast.IASTDeclaration;
import org.eclipse.cdt.core.dom.ast.IASTName;
import org.eclipse.cdt.core.dom.ast.IVariable;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPASTForStatement;


@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class CPPVariable { //TODO: add file location in toString()

    private String name;

    private CPPType type;

    @XmlTransient
    private IASTName astName;

    @XmlTransient
    // declaration.parent() can be a IASTDeclarationStatement if the variable is declared inside a function
    private IASTDeclaration declaration; //can be used to find insertion point after declaration statement.

    @XmlTransient
    private IVariable variable;


    public CPPVariable() {
    }

    public CPPVariable(IASTName astName, IASTDeclaration declaration) {
        this.astName = astName;
        this.declaration = declaration;
        this.variable = (IVariable) astName.getBinding();
        this.name = variable.getName();
        this.type = new CPPType(variable);
    }


    public String getName() {
        return name;
    }

    public CPPType getType() {
        return type;
    }

    public IASTName getAstName() {
        return astName;
    }

    public IASTDeclaration getDeclaration() {
        return declaration;
    }

    public IVariable getVariable() {
        return variable;
    }

    public ICPPASTForStatement getForLoopStatement() {
        return isForLoopInitializer() ? ((ICPPASTForStatement) declaration.getParent().getParent()) : null;
    }

    public boolean isForLoopInitializer() {
        return declaration.getParent() != null ? declaration.getParent().getParent() instanceof ICPPASTForStatement : false;
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
        if (!(obj instanceof CPPVariable)) {
            return false;
        }
        CPPVariable other = (CPPVariable) obj;
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

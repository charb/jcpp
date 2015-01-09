package jcpp.parser.cpp;

import javax.xml.bind.annotation.XmlEnum;

import org.eclipse.cdt.core.dom.ast.cpp.ICPPASTVisibilityLabel;


@XmlEnum(String.class)
public enum CPPVisibilityLabel {

    PUBLIC(ICPPASTVisibilityLabel.v_public), PROTECTED(ICPPASTVisibilityLabel.v_protected), PRIVATE(ICPPASTVisibilityLabel.v_private), UNKNOWN(-1);

    private int label;


    CPPVisibilityLabel(int label) {
        this.label = label;
    }


    public static CPPVisibilityLabel getVisibilityLabel(int label) {
        if (label == ICPPASTVisibilityLabel.v_public) {
            return PUBLIC;
        } else if (label == ICPPASTVisibilityLabel.v_protected) {
            return PROTECTED;
        } else if (label == ICPPASTVisibilityLabel.v_private) {
            return PRIVATE;
        }
        return UNKNOWN;
    }

    public int getVisibilityLabel() {
        return label;
    }

}

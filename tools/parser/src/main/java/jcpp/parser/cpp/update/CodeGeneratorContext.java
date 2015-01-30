package jcpp.parser.cpp.update;

import org.eclipse.cdt.core.dom.ast.IASTFileLocation;
import org.eclipse.cdt.core.dom.ast.IASTMacroExpansionLocation;
import org.eclipse.cdt.core.dom.ast.IASTNode;
import org.eclipse.cdt.core.dom.ast.IASTNodeLocation;
import org.eclipse.cdt.internal.core.dom.parser.ASTNode;

public class CodeGeneratorContext {

    private int offset;
    private int length;
    private UpdatesResult updatesResult;

    public CodeGeneratorContext(int offset, int length, UpdatesResult updatesResult) {
        this.offset = offset;
        this.length = length;
        this.updatesResult = updatesResult;
    }

    public CodeGeneratorContext(IASTNode node, UpdatesResult updatesResult) {
        IASTFileLocation fileLocation = getFileLocation(node);
        this.offset = fileLocation != null ? fileLocation.getNodeOffset() : -1;
        this.length = fileLocation != null ? fileLocation.getNodeLength() : -1;
        this.updatesResult = updatesResult;
    }

    public int getOffset() {
        return offset;
    }

    public int getLength() {
        return length;
    }

    public UpdatesResult getUpdatesResult() {
        return updatesResult;
    }

    public String getSourceContext() {
        if (length < 0) {
            return null;
        }
        return updatesResult.getSubstring(offset, length);
    }

    public String getSourceContext(IASTNode node) {
        IASTFileLocation fileLocation = getFileLocation(node);
        if (fileLocation != null) {
            return updatesResult.getSubstring(fileLocation.getNodeOffset(), fileLocation.getNodeLength());
        }
        return null;
    }

    public static IASTFileLocation getFileLocation(IASTNode node) {
        IASTNodeLocation[] nodeLocations = node.getNodeLocations();
        IASTFileLocation fileLocation = null;
        if (nodeLocations.length == 1 && nodeLocations[0] instanceof IASTMacroExpansionLocation) {
            fileLocation = ((ASTNode) node).getImageLocation(); //NOTE: can return null when the cppVariable is declared in a marco definition.
        } else {
            fileLocation = node.getFileLocation();
        }
        return fileLocation;
    }

}

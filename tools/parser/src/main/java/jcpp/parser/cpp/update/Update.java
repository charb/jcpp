package jcpp.parser.cpp.update;

import org.eclipse.cdt.core.dom.ast.IASTNode;


public abstract class Update implements Comparable<Update> {

    private IASTNode node;
    private int manualOffset;


    public Update(IASTNode node) {
        this.node = node;
    }

    public Update(int manualOffset) {
        this.node = null;
        this.manualOffset = manualOffset;
    }


    public abstract void update(UpdatesResult updatesResult) throws Exception;

    @Override
    public int compareTo(Update u) {
        if (getOffset() > u.getOffset()) {
            return -1;
        }
        return 1;
    }

    private int getOffset() {
        return node != null ? node.getFileLocation().getNodeOffset() : manualOffset;
    }

}

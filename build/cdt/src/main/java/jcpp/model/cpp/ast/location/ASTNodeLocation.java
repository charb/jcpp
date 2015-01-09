package jcpp.model.cpp.ast.location;

import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTNodeLocation{
	@XmlAttribute
	private int nodeLength;
	@XmlAttribute
	private int nodeOffset;

	public ASTNodeLocation(IASTNodeLocation nodeLocation) throws Exception{
		nodeLength=nodeLocation.getNodeLength();
		nodeOffset=nodeLocation.getNodeOffset();
	}

	public ASTNodeLocation(){
	}

	public int getNodeLength(){
		return nodeLength;
	}

	public void setNodeLength(int i){
		nodeLength=i;
	}

	public int getNodeOffset(){
		return nodeOffset;
	}

	public void setNodeOffset(int i){
		nodeOffset=i;
	}
}
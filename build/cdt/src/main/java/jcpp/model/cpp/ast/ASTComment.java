package jcpp.model.cpp.ast;

import jcpp.model.cpp.ast.location.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;
import java.util.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTComment extends ASTNode{
	@XmlElement
	private String comment;
	@XmlElement
	private boolean bIsBlockComment;
	@XmlElement
	private ASTNodeWrapper<ASTFileLocation> fileLocation;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTNodeLocation> nodeLocations;

	public ASTComment(IASTComment node) throws Exception{
		super(node);
		comment=new String(node.getComment());
		bIsBlockComment=node.isBlockComment();
		fileLocation=new ASTNodeWrapper<ASTFileLocation>();
		if (node.getFileLocation()!=null){
			fileLocation.set((ASTFileLocation)ASTNodeLocationFactory.create(node.getFileLocation()));
		}
		nodeLocations=new ArrayList<ASTNodeLocation>();
		if (node.getNodeLocations()!=null){
			for (IASTNodeLocation l : node.getNodeLocations()){
				nodeLocations.add(ASTNodeLocationFactory.create(l));
			}
		}
	}

	public ASTComment(){
	}

	public String getComment(){
		return comment;
	}

	public void setComment(String c){
		comment=c;
	}

	public boolean isBlockComment(){
		return bIsBlockComment;
	}

	public void setBlockComment(boolean b){
		bIsBlockComment=b;
	}

	public ASTFileLocation getFileLocation(){
		return fileLocation.get();
	}

	public void setFileLocation(ASTFileLocation l){
		fileLocation.set(l);
	}

	public List<ASTNodeLocation> getNodeLocations(){
		return nodeLocations;
	}

	public void addNodeLocation(ASTNodeLocation l){
		nodeLocations.add(l);
	}
}
package jcpp.model.cpp.ast.name;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.location.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTName extends ASTNode{
	@XmlAttribute
	private boolean bIsReference;
	@XmlAttribute
	private boolean bIsDefinition;
	@XmlAttribute
	private boolean bIsDeclaration;
	@XmlAttribute
	private String simpleID;
	@XmlElement
	private ASTNodeWrapper<ASTFileLocation> fileLocation; 
	@XmlElement
	private ASTNodeWrapper<ASTImageLocation> imageLocation;
	@XmlAttribute
	private boolean bIsQualified;
	@XmlElement
	private String name;

	public ASTName(IASTName name) throws Exception{
		super(name);
		bIsReference=name.isReference();
		bIsDefinition=name.isDefinition();
		bIsDeclaration=name.isDeclaration();
		simpleID=new String(name.getSimpleID());
		fileLocation=new ASTNodeWrapper<ASTFileLocation>();
		if (name.getFileLocation()!=null){
			fileLocation.set((ASTFileLocation)ASTNodeLocationFactory.create(name.getFileLocation()));
		}

		imageLocation=new ASTNodeWrapper<ASTImageLocation>();
		if (name.getImageLocation()!=null){
			imageLocation.set(new ASTImageLocation(name.getImageLocation()));
		}
		bIsQualified=name.isQualified();
		this.name=new String(name.toCharArray());
	}

	public ASTName(){
		fileLocation=new ASTNodeWrapper<ASTFileLocation>();
		imageLocation=new ASTNodeWrapper<ASTImageLocation>();
	}

	public ASTImageLocation getImageLocation(){
		return imageLocation.get();
	}

	public boolean isReference(){
		return bIsReference;
	}

	public void setReference(boolean b){
		bIsReference=b;
	}

	public boolean isDefinition(){
		return bIsDefinition;
	}

	public void setDefinition(boolean b){
		bIsDefinition=b;
	}

	public boolean isDeclaration(){
		return bIsDeclaration;
	}

	public void setDeclaration(boolean b){
		bIsDeclaration=b;
	}

	public String getSimpleID(){
		return simpleID;
	}

	public void setSimpleID(String s){
		simpleID=s;
	}

	public ASTFileLocation getFileLocation(){
		return fileLocation.get();
	} 

	public void setFileLocation(ASTFileLocation l){
		fileLocation.set(l);
	}

	public void setImageLocation(ASTImageLocation l){
		imageLocation.set(l);
	}

	public boolean isQualified(){
		return bIsQualified;
	}

	public void setIsQualified(boolean b){
		bIsQualified=b;
	}

	public String getName(){
		return name;
	}

	public void setName(String n){
		name=n;
	}
}
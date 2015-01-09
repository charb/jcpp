package jcpp.model.cpp.ast;

import jcpp.model.cpp.ast.location.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.parser.*;
import java.util.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTProblem extends ASTNode{
	@XmlElement
	private int id;
	@XmlElement
	private String message;
	@XmlElement
	private String messageWithLocation;
	@XmlElement
	@XmlElementWrapper
	private List<String> arguments;
	@XmlElement
	private String originatingFileName;
	@XmlElement
	private int sourceStart;
	@XmlElement
	private int sourceEnd;
	@XmlElement
	private int souceLineNumber;
	@XmlElement
	private boolean bIsError;
	@XmlElement
	private boolean bIsWarning;

	public ASTProblem(IASTProblem pb) throws Exception{
		super(pb);
		id=pb.getID();
		message=pb.getMessage();
		messageWithLocation=pb.getMessageWithLocation();
		arguments=new ArrayList<String>();
		if (pb.getArguments()!=null){
			for (String s : pb.getArguments()){
				arguments.add(s);
			}
		}

		originatingFileName=new String(pb.getOriginatingFileName());
		sourceStart=pb.getSourceStart();
		sourceEnd=pb.getSourceEnd();
		souceLineNumber=pb.getSourceLineNumber();
		bIsError=pb.isError();
		bIsWarning=pb.isWarning();
	}

	public ASTProblem(){
	}

	public List<String> getArguments(){
		return arguments;
	}

	public void addArgument(String s){
		arguments.add(s);
	} 

	public int getID(){
		return id;
	}

	public void setID(int i){
		id=i;
	}

	public String getMessage(){
		return message;
	}

	public void setMessage(String i){
		message=i;
	}

	public String getMessageWithLocation(){
		return messageWithLocation;
	}

	public void setMessageWithLocation(String i){
		messageWithLocation=i;
	}

	public String getOriginatingFileName(){
		return originatingFileName;
	}

	public void setOriginatingFileName(String i){
		originatingFileName=i;
	}

	public int getSourceStart(){
		return sourceStart;
	}

	public void setSourceStart(int i){
		sourceStart=i;
	}

	public int getSourceEnd(){
		return sourceEnd;
	}

	public void setSourceEnd(int i){
		sourceEnd=i;
	}

	public int getSouceLineNumber(){
		return souceLineNumber;
	}

	public void setSouceLineNumber(int i){
		souceLineNumber=i;
	}

	public boolean isError(){
		return bIsError;
	}

	public void setIsError(boolean b){
		bIsError=b;
	}

	public boolean isWarning(){
		return bIsWarning;
	}

	public void setIsWarning(boolean b){
		bIsWarning=b;
	}
}
package jcpp.model.cpp.ast.location;

import jcpp.model.cpp.ast.macro.*;
import jcpp.model.cpp.ast.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTFileLocation extends ASTNodeLocation{
	@XmlAttribute
	private int endingLineNumber;
	@XmlAttribute
	private String fileName;
	@XmlAttribute
	private int startingLineNumber;

	public ASTFileLocation(IASTFileLocation location) throws Exception{
		super(location);
		endingLineNumber=location.getEndingLineNumber();
		fileName=location.getFileName();
		startingLineNumber=location.getStartingLineNumber();
	}

	public ASTFileLocation(){
	}

	public int getEndingLineNumber(){
		return endingLineNumber;
	}

	public void setEndingLineNumber(int i){
		endingLineNumber=i;
	}

	public String getFileName(){
		return fileName;
	}

	public void setFileName(String i){
		fileName=i;
	}

	public int getStartingLineNumber(){
		return startingLineNumber;
	}

	public void setStartingLineNumber(int i){
		startingLineNumber=i;
	}
}
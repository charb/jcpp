package jcpp.model.cpp.ast.location;

import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTImageLocation extends ASTFileLocation{
	@XmlAttribute
	private String locationKind;

	public ASTImageLocation(IASTImageLocation location) throws Exception{
		super(location);
		locationKind=getLocationKind(location.getLocationKind());
	}

	public ASTImageLocation(){
	}

	public static String getLocationKind(int i){
		if (i==IASTImageLocation.ARGUMENT_TO_MACRO_EXPANSION){
			return "ARGUMENT_TO_MACRO_EXPANSION";
		}else if(i==IASTImageLocation.MACRO_DEFINITION){
			return "MACRO_DEFINITION";
		}else if(i==IASTImageLocation.REGULAR_CODE){
			return "REGULAR_CODE";
		}else{
			return "unknown";
		}
	}

	public String getLocationKind(){
		return locationKind;
	}

	public void setLocationKind(String i){
		locationKind=i;
	}
}
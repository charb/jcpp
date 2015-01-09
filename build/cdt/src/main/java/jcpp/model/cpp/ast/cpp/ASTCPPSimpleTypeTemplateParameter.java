package jcpp.model.cpp.ast.cpp;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.id.*;
import jcpp.model.cpp.ast.name.*;
import jcpp.model.cpp.ast.attribute.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPSimpleTypeTemplateParameter extends ASTCPPTemplateParameter{
	@XmlElement
	private ASTNodeWrapper<ASTTypeId> defaultType;
	@XmlElement
	private ASTNodeWrapper<ASTName> name;
	@XmlElement
	private String parameterType;

	public ASTCPPSimpleTypeTemplateParameter(ICPPASTSimpleTypeTemplateParameter p) throws Exception{
		super(p);
		defaultType=new ASTNodeWrapper<ASTTypeId>();
		if (p.getDefaultType()!=null){
			defaultType.set(ASTTypeIdFactory.create(p.getDefaultType()));
		}
		name=new ASTNodeWrapper<ASTName>();
		if (p.getName()!=null){
			name.set(ASTNameFactory.create(p.getName()));
		}
		parameterType=getParameterType(p.getParameterType());
	}

	public ASTCPPSimpleTypeTemplateParameter(){
		defaultType=new ASTNodeWrapper<ASTTypeId>();
		name=new ASTNodeWrapper<ASTName>();
	}

	public ASTTypeId getDefaultType(){
		return defaultType.get();
	}

	public void setDefaultType(ASTTypeId b){
		defaultType.set(b);
	}

	public ASTName getName(){
		return name.get();
	}

	public void setName(ASTName b){
		name.set(b);
	}

	public static String getParameterType(int i){
		if (i==ICPPASTSimpleTypeTemplateParameter.st_class){
			return "st_class";
		}else if (i==ICPPASTSimpleTypeTemplateParameter.st_typename){
			return "st_typename";
		}else{
			return "unknown";
		}
	}

	public String getParameterType(){
		return parameterType;
	}

	public void setParameterType(String b){
		parameterType=b;
	}
}
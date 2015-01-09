package jcpp.model.cpp.ast.stmt;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.expr.*;
import jcpp.model.cpp.ast.name.*;
import jcpp.model.cpp.ast.expr.init.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTLabelStatement extends ASTStatement{
	@XmlElement
	private ASTNodeWrapper<ASTName> name;
	@XmlElement
	private ASTNodeWrapper<ASTStatement> nestedStatement;

	public ASTLabelStatement(IASTLabelStatement s) throws Exception{
		super(s);
		name=new ASTNodeWrapper<ASTName>();
		if (s.getName()!=null){
			name.set(ASTNameFactory.create(s.getName()));
		}

		nestedStatement=new ASTNodeWrapper<ASTStatement>();
		if (s.getNestedStatement()!=null){
			nestedStatement.set(ASTStatementFactory.create(s.getNestedStatement()));
		}
	}

	public ASTLabelStatement(){
		name=new ASTNodeWrapper<ASTName>();
		nestedStatement=new ASTNodeWrapper<ASTStatement>();
	}

	public ASTName getName(){
		return name.get();
	}

	public void setName(ASTName s){
		name.set(s);
	}

	public ASTStatement getNestedStatement(){
		return nestedStatement.get();
	}

	public void setNestedStatement(ASTStatement s){
		nestedStatement.set(s);
	}
}
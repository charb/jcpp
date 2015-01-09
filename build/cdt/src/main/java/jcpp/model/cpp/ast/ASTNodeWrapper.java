package jcpp.model.cpp.ast;

import org.eclipse.cdt.core.dom.ast.*;
import jcpp.model.cpp.ast.location.*;
import java.util.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTNodeWrapper<T>{
	@XmlAnyElement
	private T node;

	public ASTNodeWrapper(){
	}

	public T get(){
		return node;
	}

	public void set(T s){
		node=s;
	}
}
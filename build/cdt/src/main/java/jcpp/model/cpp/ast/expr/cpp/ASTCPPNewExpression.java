package jcpp.model.cpp.ast.expr.cpp;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.expr.init.*;
import jcpp.model.cpp.ast.name.*;
import java.util.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import jcpp.model.cpp.ast.id.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPNewExpression extends ASTCPPExpression{
	@XmlElement
	private ASTNodeWrapper<ASTInitializer> initializer;
	@XmlElement
	private ASTNodeWrapper<ASTTypeId> typeId;
	@XmlElement
	private boolean bIsArrayAllocation;
	@XmlElement
	private boolean bIsGlobal;
	@XmlElement
	private boolean bIsNewTypeId;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTInitializerClause> placementArguments;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTImplicitName> implicitNames; 

	public ASTCPPNewExpression(ICPPASTNewExpression expr) throws Exception{
		super(expr);

		initializer=new ASTNodeWrapper<ASTInitializer>();
		if (expr.getInitializer()!=null){
			initializer.set(ASTInitializerFactory.create(expr.getInitializer()));
		}

		placementArguments=new ArrayList<ASTInitializerClause>();
		if (expr.getPlacementArguments()!=null){
			for (IASTInitializerClause c : expr.getPlacementArguments()){
				placementArguments.add(ASTInitializerClauseFactory.create(c));
			}
		}
		
		typeId=new ASTNodeWrapper<ASTTypeId>();
		if (expr.getTypeId()!=null){
			typeId.set(ASTTypeIdFactory.create(expr.getTypeId()));
		}
		
		bIsArrayAllocation=expr.isArrayAllocation();
		bIsGlobal=expr.isGlobal();
		bIsNewTypeId=expr.isNewTypeId();

		implicitNames=new ArrayList<ASTImplicitName>();
		if (expr.getImplicitNames()!=null){
			for (IASTImplicitName n : expr.getImplicitNames()){
				implicitNames.add((ASTImplicitName)ASTNameFactory.create(n));
			}
		}
	}

	public ASTCPPNewExpression(){
		initializer=new ASTNodeWrapper<ASTInitializer>();
		typeId=new ASTNodeWrapper<ASTTypeId>();
	}

	public ASTInitializer getInitializer(){
		return initializer.get();
	}

	public void setInitializer(ASTInitializer b){
		initializer.set(b);
	}

	public List<ASTInitializerClause> getPlacementArguments(){
		return placementArguments;
	}

	public void addPlacementArgument(ASTInitializerClause a){
		placementArguments.add(a);
	}

	public ASTTypeId getTypeId(){
		return typeId.get();
	}

	public void setTypeId(ASTTypeId b){
		typeId.set(b);
	}

	public boolean isArrayAllocation(){
		return bIsArrayAllocation;
	}

	public void setIsArrayAllocation(boolean b){
		bIsArrayAllocation=b;
	}

	public boolean isGlobal(){
		return bIsGlobal;
	}

	public void setIsGlobal(boolean b){
		bIsGlobal=b;
	}

	public boolean isNewTypeId(){
		return bIsNewTypeId;
	}

	public void setIsNewTypeId(boolean b){
		bIsNewTypeId=b;
	}

	public List<ASTImplicitName> getImplicitNames(){
		return implicitNames;
	}

	public void addImplicitName(ASTImplicitName n){
		implicitNames.add(n);
	}
}
package jcpp.model.cpp.ast.declarator.cpp;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.declarator.*;
import jcpp.model.cpp.ast.declaration.*;
import jcpp.model.cpp.ast.declaration.cpp.*;
import jcpp.model.cpp.ast.declaration.specifier.*;
import jcpp.model.cpp.ast.declaration.specifier.cpp.*;
import jcpp.model.cpp.ast.expr.*;
import jcpp.model.cpp.ast.expr.cpp.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import jcpp.model.cpp.ast.id.*;
import java.util.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTCPPFunctionDeclarator extends ASTStandardFunctionDeclarator{
	@XmlElement
	private ASTNodeWrapper<ASTCPPExpression> noexceptExpression;
	@XmlElement
	private ASTNodeWrapper<ASTTypeId> trailingReturnType;
	@XmlElement
	private boolean bIsConst;
	@XmlElement
	private boolean bIsFinal;
	@XmlElement
	private boolean bIsMutable;
	@XmlElement
	private boolean bIsOverride;
	@XmlElement
	private boolean bIsPureVirtual;
	@XmlElement
	private boolean bIsVolatile;
	@XmlElement
	private boolean bDeclaresParameterPack;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTCPPVirtSpecifier> virtSpecifiers;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTTypeId> exceptionSpecification;

	public ASTCPPFunctionDeclarator(ICPPASTFunctionDeclarator decl) throws Exception{
		super(decl);
		exceptionSpecification=new ArrayList<ASTTypeId>();
		if (decl.getExceptionSpecification()!=null){
			for (IASTTypeId i : decl.getExceptionSpecification()){
				exceptionSpecification.add(ASTTypeIdFactory.create(i));
			}
		}

		noexceptExpression=new ASTNodeWrapper<ASTCPPExpression>();
		if (decl.getNoexceptExpression()!=null){
			noexceptExpression.set((ASTCPPExpression)ASTExpressionFactory.create(decl.getNoexceptExpression()));
		}

		trailingReturnType=new ASTNodeWrapper<ASTTypeId>();
		if (decl.getTrailingReturnType()!=null){
			trailingReturnType.set(ASTTypeIdFactory.create(decl.getTrailingReturnType()));
		}

		virtSpecifiers=new ArrayList<ASTCPPVirtSpecifier>();
		if (decl.getVirtSpecifiers()!=null){
			for (ICPPASTVirtSpecifier i : decl.getVirtSpecifiers()){
				virtSpecifiers.add(new ASTCPPVirtSpecifier(i));
			}
		}

		bIsConst=decl.isConst();
		bIsFinal=decl.isFinal();
		bIsMutable=decl.isMutable();
		bIsOverride=decl.isOverride();
		bIsPureVirtual=decl.isPureVirtual();
		bIsVolatile=decl.isVolatile();
		bDeclaresParameterPack=decl.declaresParameterPack();
	}

	public ASTCPPFunctionDeclarator(){
		noexceptExpression=new ASTNodeWrapper<ASTCPPExpression>();
		trailingReturnType=new ASTNodeWrapper<ASTTypeId>();
	}

	public List<ASTTypeId> getExceptionSpecification(){
		return exceptionSpecification;
	}

	public void addExceptionSpecification(ASTTypeId i){
		exceptionSpecification.add(i);
	}

	public ASTCPPExpression getNoexceptExpression(){
		return noexceptExpression.get();
	}

	public void setNoexceptExpression(ASTCPPExpression e){
		noexceptExpression.set(e);
	}

	public ASTTypeId getTrailingReturnType(){
		return trailingReturnType.get();
	}

	public void setTrailingReturnType(ASTTypeId i){
		trailingReturnType.set(i);
	}

	public List<ASTCPPVirtSpecifier> getVirtSpecifiers(){
		return virtSpecifiers;
	}

	public void addVirtSpecifier(ASTCPPVirtSpecifier vs){
		virtSpecifiers.add(vs);
	}

	public boolean isConst(){
		return bIsConst;
	}

	public void setIsConst(boolean b){
		bIsConst=b;
	}

	public boolean isFinal(){
		return bIsFinal;
	}

	public void setIsFinal(boolean b){
		bIsFinal=b;
	}

	public boolean isMutable(){
		return bIsMutable;
	}

	public void setIsMutable(boolean b){
		bIsMutable=b;
	}

	public boolean isOverride(){
		return bIsOverride;
	}

	public void setIsOverride(boolean b){
		bIsOverride=b;
	}

	public boolean isPureVirtual(){
		return bIsPureVirtual;
	}

	public void setIsPureVirtual(boolean b){
		bIsPureVirtual=b;
	}

	public boolean isVolatile(){
		return bIsVolatile;
	}

	public void setIsVolatile(boolean b){
		bIsVolatile=b;
	}

	public boolean declaresParameterPack(){
		return bDeclaresParameterPack;
	}

	public void setDeclaresParameterPack(boolean b){
		bDeclaresParameterPack=b;
	}
}
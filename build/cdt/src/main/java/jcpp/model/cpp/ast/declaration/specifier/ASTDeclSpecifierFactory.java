package jcpp.model.cpp.ast.declaration.specifier;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.declaration.specifier.c.*;
import jcpp.model.cpp.ast.declaration.specifier.cpp.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.c.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import java.util.*;

public class ASTDeclSpecifierFactory{

	public static void fillClasses(List<Class> c){
		c.add(ASTCPPVirtSpecifier.class);
		c.add(ASTCPPTypeTransformationSpecifier.class);
		c.add(ASTCPPSimpleDeclSpecifier.class);
		c.add(ASTCPPNamedTypeSpecifier.class);
		c.add(ASTCPPEnumerationSpecifier.class);
		c.add(ASTCPPElaboratedTypeSpecifier.class);
		c.add(ASTCPPCompositeTypeSpecifier.class);
		c.add(ASTCPPClassVirtSpecifier.class);
		c.add(ASTCPPBaseSpecifier.class);
		c.add(ASTCPPDeclSpecifier.class);
		c.add(ASTCTypedefNameSpecifier.class);
		c.add(ASTCEnumerationSpecifier.class);
		c.add(ASTCElaboratedTypeSpecifier.class);
		c.add(ASTCCompositeTypeSpecifier.class);
		c.add(ASTCSimpleDeclSpecifier.class);
		c.add(ASTCDeclSpecifier.class);
		c.add(ASTSimpleDeclSpecifier.class);
		c.add(ASTNamedTypeSpecifier.class);
		c.add(ASTEnumerationSpecifier.class);
		c.add(ASTElaboratedTypeSpecifier.class);
		c.add(ASTCompositeTypeSpecifier.class);
		c.add(ASTDeclSpecifier.class);
	}

	public static boolean handleNode(IASTNode s){
		return (s instanceof ICPPASTVirtSpecifier || s instanceof ICPPASTTypeTransformationSpecifier ||
				s instanceof ICPPASTSimpleDeclSpecifier || s instanceof ICPPASTNamedTypeSpecifier ||
				s instanceof ICPPASTEnumerationSpecifier || s instanceof ICPPASTElaboratedTypeSpecifier ||
				s instanceof ICPPASTCompositeTypeSpecifier || s instanceof ICPPASTClassVirtSpecifier ||
				s instanceof ICPPASTCompositeTypeSpecifier.ICPPASTBaseSpecifier || s instanceof ICPPASTDeclSpecifier ||
				s instanceof ICASTTypedefNameSpecifier || s instanceof ICASTEnumerationSpecifier || 
				s instanceof ICASTElaboratedTypeSpecifier || s instanceof ICASTCompositeTypeSpecifier ||
				s instanceof ICASTSimpleDeclSpecifier || s instanceof ICASTDeclSpecifier ||
				s instanceof IASTSimpleDeclSpecifier || s instanceof IASTNamedTypeSpecifier ||
				s instanceof IASTEnumerationSpecifier || s instanceof IASTElaboratedTypeSpecifier ||
				s instanceof IASTCompositeTypeSpecifier || s instanceof IASTDeclSpecifier);
	}

	public static ASTNode create(IASTNode s) throws Exception{
		if (s instanceof ICPPASTVirtSpecifier){
			return new ASTCPPVirtSpecifier((ICPPASTVirtSpecifier)s);
		
		}else if (s instanceof ICPPASTTypeTransformationSpecifier){
			return new ASTCPPTypeTransformationSpecifier((ICPPASTTypeTransformationSpecifier)s);

		}else if (s instanceof ICPPASTSimpleDeclSpecifier){
			return new ASTCPPSimpleDeclSpecifier((ICPPASTSimpleDeclSpecifier)s);

		}else if (s instanceof ICPPASTNamedTypeSpecifier){
			return new ASTCPPNamedTypeSpecifier((ICPPASTNamedTypeSpecifier)s);

		}else if (s instanceof ICPPASTEnumerationSpecifier){
			return new ASTCPPEnumerationSpecifier((ICPPASTEnumerationSpecifier)s);

		}else if (s instanceof ICPPASTElaboratedTypeSpecifier){
			return new ASTCPPElaboratedTypeSpecifier((ICPPASTElaboratedTypeSpecifier)s);

		}else if (s instanceof ICPPASTCompositeTypeSpecifier){
			return new ASTCPPCompositeTypeSpecifier((ICPPASTCompositeTypeSpecifier)s);

		}else if (s instanceof ICPPASTClassVirtSpecifier){
			return new ASTCPPClassVirtSpecifier((ICPPASTClassVirtSpecifier)s);

		}else if (s instanceof ICPPASTCompositeTypeSpecifier.ICPPASTBaseSpecifier){
			return new ASTCPPBaseSpecifier((ICPPASTCompositeTypeSpecifier.ICPPASTBaseSpecifier)s);

		}else if (s instanceof ICPPASTDeclSpecifier){
			return new ASTCPPDeclSpecifier((ICPPASTDeclSpecifier)s);

		}else if (s instanceof ICASTTypedefNameSpecifier){
			return new ASTCTypedefNameSpecifier((ICASTTypedefNameSpecifier)s);

		}else if (s instanceof ICASTEnumerationSpecifier){
			return new ASTCEnumerationSpecifier((ICASTEnumerationSpecifier)s);

		}else if (s instanceof ICASTElaboratedTypeSpecifier){
			return new ASTCElaboratedTypeSpecifier((ICASTElaboratedTypeSpecifier)s);

		}else if (s instanceof ICASTCompositeTypeSpecifier){
			return new ASTCCompositeTypeSpecifier((ICASTCompositeTypeSpecifier)s);

		}else if (s instanceof ICASTSimpleDeclSpecifier){
			return new ASTCSimpleDeclSpecifier((ICASTSimpleDeclSpecifier)s);
		
		}else if (s instanceof ICASTDeclSpecifier){
			return new ASTCDeclSpecifier((ICASTDeclSpecifier)s);
			
		}else if (s instanceof IASTSimpleDeclSpecifier){
			return new ASTSimpleDeclSpecifier((IASTSimpleDeclSpecifier)s);

		}else if (s instanceof IASTNamedTypeSpecifier){
			return new ASTNamedTypeSpecifier((IASTNamedTypeSpecifier)s);
		
		}else if (s instanceof IASTEnumerationSpecifier){
			return new ASTEnumerationSpecifier((IASTEnumerationSpecifier)s);
			
		}else if (s instanceof IASTElaboratedTypeSpecifier){
			return new ASTElaboratedTypeSpecifier((IASTElaboratedTypeSpecifier)s);
			
		}else if (s instanceof IASTCompositeTypeSpecifier){
			return new ASTCompositeTypeSpecifier((IASTCompositeTypeSpecifier)s);

		}else if (s instanceof IASTDeclSpecifier){
			return new ASTDeclSpecifier((IASTDeclSpecifier)s);
		}

		throw new Exception("unknown declaration specifier "+s.getClass()+", raw signature: "+s.getRawSignature());
	}
}
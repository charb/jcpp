package jcpp.mavenplugin.code.gc;

import java.util.HashMap;
import java.util.IdentityHashMap;
import java.util.Map;

import jcpp.parser.cpp.CPPClass;
import jcpp.parser.cpp.CPPFile;
import jcpp.parser.cpp.CPPVariable;

import org.eclipse.cdt.core.dom.ast.IASTFunctionDefinition;
import org.eclipse.cdt.core.dom.ast.IASTNode;

public class GcFileTupleContext {

	private boolean headerUpdater;

	private final CPPFile headerCPPFile;
	private final CPPFile cppCPPFile;

	private final Map<String, GcClassContext> classContexts;
	private final Map<IASTFunctionDefinition, Integer> currentVariableIndexByFunction;
	
	public GcFileTupleContext(CPPFile headerCPPFile, CPPFile cppCPPFile) {
		this.headerCPPFile = headerCPPFile;
		this.cppCPPFile = cppCPPFile;
		this.currentVariableIndexByFunction = new IdentityHashMap<IASTFunctionDefinition, Integer>();
		this.classContexts = new HashMap<String, GcClassContext>();
		
		if (headerCPPFile != null) {
			for (CPPClass cppClass : headerCPPFile.getClasses()) {
				classContexts.put(cppClass.getName(), new GcClassContext(cppClass));
			}
		}
		
		if(cppCPPFile != null) {
			for (CPPClass cppClass : cppCPPFile.getClasses()) {
				if(!classContexts.containsKey(cppClass.getName())) {
					classContexts.put(cppClass.getName(), new GcClassContext(cppClass));
				}
			}
		}

	}

	public boolean isHeaderUpdater() {
		return headerUpdater;
	}

	public void setHeaderUpdater(boolean headerUpdater) {
		this.headerUpdater = headerUpdater;
	}

	public CPPFile getHeaderCPPFile() {
		return headerCPPFile;
	}

	public CPPFile getCppCPPFile() {
		return cppCPPFile;
	}
	
	public GcClassContext getClassContext(String name) {
		return classContexts.get(name);
	}
	
	public int getCurrentVariableIndex(CPPVariable cppVariable) {
		IASTNode declaration = cppVariable.getDeclaration().getParent();
		IASTFunctionDefinition functionDefinition = null;
		while(declaration != null) {
			if(declaration instanceof IASTFunctionDefinition) {
				functionDefinition = (IASTFunctionDefinition) declaration;
				break;
			}
			declaration = declaration.getParent();
		}
		Integer index = currentVariableIndexByFunction.get(functionDefinition);
		int returnIndex = 0;
		if(index != null) {
			returnIndex = index.intValue() + 1;
		}
		currentVariableIndexByFunction.put(functionDefinition, Integer.valueOf(returnIndex));
		return returnIndex;
	}

}

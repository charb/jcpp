package jcpp.parser.cpp.update;

import java.util.*;
import java.io.*;
import org.eclipse.cdt.core.dom.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import org.eclipse.cdt.core.dom.ast.c.*;
import org.eclipse.cdt.core.dom.ast.*;
import org.eclipse.cdt.core.dom.ast.gnu.cpp.*;
import org.eclipse.cdt.core.parser.*;
import org.eclipse.cdt.internal.core.dom.parser.*;
import org.eclipse.cdt.core.index.*;
import org.eclipse.cdt.internal.core.parser.*;
import org.eclipse.cdt.internal.core.parser.scanner.*;

public class ReplaceMacroUpdate extends Update{
	private IASTName name;
	private String macroToFind;
	private String macroToInsert;

	public ReplaceMacroUpdate(IASTName name,String macroToFind,String macroToInsert){
		super(name);
		this.name=name;
		this.macroToFind=macroToFind;
		this.macroToInsert=macroToInsert;
	}

	public void update(UpdatesResult updatesResult) throws Exception{
		updatesResult.replace(name.getFileLocation().getNodeOffset(),name.getFileLocation().getNodeOffset()+macroToFind.length(),macroToInsert);
	}
}
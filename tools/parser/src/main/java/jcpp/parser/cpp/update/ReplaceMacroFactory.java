package jcpp.parser.cpp.update;

import jcpp.parser.cpp.*;
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

public class ReplaceMacroFactory extends UpdateFactory{
	private String macroToFind;
	private String macroToInsert;

	public ReplaceMacroFactory(String macroToFind,String macroToInsert){
		this.macroToFind=macroToFind;
		this.macroToInsert=macroToInsert;
	}

	public List<Update> createUpdates(CPPFile cppFile) throws Exception{
		List<Update> updates=new ArrayList<Update>();
		IASTTranslationUnit unit=cppFile.getTranslationUnit();
		IASTPreprocessorMacroExpansion[] macros=unit.getMacroExpansions();
        if (macros!=null){
            for (IASTPreprocessorMacroExpansion macro : macros){
                IASTName n = macro.getMacroReference();
                if (new String(n.toCharArray()).equals(macroToFind)){
                	updates.add(new ReplaceMacroUpdate(n,macroToFind,macroToInsert));
                }
            }
        }
        return updates;
	}
}
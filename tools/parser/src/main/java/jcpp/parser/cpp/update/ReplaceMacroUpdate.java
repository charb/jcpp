package jcpp.parser.cpp.update;

import org.eclipse.cdt.core.dom.ast.IASTName;

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
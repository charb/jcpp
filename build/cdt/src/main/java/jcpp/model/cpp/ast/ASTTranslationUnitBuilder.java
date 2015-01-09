package jcpp.model.cpp.ast;

import org.eclipse.cdt.core.dom.ast.*;
import jcpp.model.cpp.ast.location.*;
import jcpp.model.cpp.ast.declaration.*;
import jcpp.model.cpp.ast.macro.*;
import jcpp.model.cpp.ast.stmt.*;
import java.util.*;
import java.io.*;
import org.eclipse.cdt.core.dom.*;
import org.eclipse.cdt.core.dom.ast.cpp.*;
import org.eclipse.cdt.core.dom.ast.c.*;
import org.eclipse.cdt.core.dom.ast.gnu.cpp.*;
import org.eclipse.cdt.core.parser.*;
import org.eclipse.cdt.internal.core.dom.parser.*;
import org.eclipse.cdt.core.index.*;
import org.eclipse.cdt.internal.core.parser.*;
import org.eclipse.cdt.internal.core.parser.scanner.*;

public class ASTTranslationUnitBuilder{
	private ASTTranslationUnitConfig config;

	public ASTTranslationUnitBuilder(){
	}

	public ASTTranslationUnitConfig getConfig(){
		return config;
	}

	public void setConfig(ASTTranslationUnitConfig c){
		config=c;
	}

	private static class FileProvider extends InternalFileContentProvider{
    	@Override
    	public InternalFileContent getContentForInclusion(String path,IMacroDictionary macroDictionary) {
        	return (InternalFileContent) InternalFileContent.createForExternalFileLocation(path);
    	}

    	@Override
    	public InternalFileContent getContentForInclusion(IIndexFileLocation arg0, String arg1) {
        	return null;
    	}
	}

	public ASTTranslationUnit build() throws Exception{
		IParserLogService log = new IParserLogService(){
              public void traceLog(String paramString){
                    System.out.println(paramString);
              }

              public boolean isTracing(){
                    return true;
              }
        };		

        File file=new File(config.getFilePath());
        IScannerInfo info = new ScannerInfo(config.getMapSymbols(),config.getIncludesPath().toArray(new String[0]));
        FileContent ct = FileContent.createForExternalFileLocation(file.getAbsolutePath());

        IASTTranslationUnit translationUnit =GPPLanguage.getDefault().getASTTranslationUnit(ct, info, new FileProvider(),null, 0,log);
        return new ASTTranslationUnit(translationUnit);
    }

	private static void fillFiles(File f,List<File> files){
   		if (f.isDirectory()){
        	for (File f1 : f.listFiles()){
            	fillFiles(f1,files);
        	}
    	}else{
        	files.add(f);
    	}
  	}

    public static void main(String[] argv) throws Exception{
        ASTTranslationUnitConfig config=ASTTranslationUnitConfig.readFrom(new FileInputStream(new File(argv[0])));
        String parentAbsolutePath=config.getFilePath();
        File parent=new File(parentAbsolutePath);
        List<File> files=new ArrayList<File>();
        fillFiles(parent,files);

        for (File f : files){
            System.out.println("Parsing file "+f.getAbsolutePath());
            String child=f.getAbsolutePath().substring(parentAbsolutePath.length());
            File newFile=new File("xml/"+child+".xml");
            newFile.getParentFile().mkdirs();
            ASTTranslationUnitBuilder builder=new ASTTranslationUnitBuilder();
    		builder.setConfig(config);
    		config.setFilePath(f.getAbsolutePath());
    		ASTTranslationUnit unit=builder.build();
            unit.keepUnderPath();
            FileOutputStream out=new FileOutputStream(newFile);
            unit.writeTo(out);
            out.close();
            System.out.println("Xml representation written to "+newFile.getAbsolutePath());
    	}
    }
}
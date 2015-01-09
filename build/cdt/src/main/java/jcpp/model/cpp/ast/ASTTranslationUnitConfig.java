package jcpp.model.cpp.ast;

import org.eclipse.cdt.core.dom.ast.*;
import jcpp.model.cpp.ast.location.*;
import jcpp.model.cpp.ast.declaration.*;
import jcpp.model.cpp.ast.macro.*;
import jcpp.model.cpp.ast.stmt.*;
import java.util.*;
import javax.xml.bind.annotation.*;
import java.io.*;
import javax.xml.bind.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTTranslationUnitConfig{
	@XmlElement
	private String filePath;
	@XmlElement
	@XmlElementWrapper(name="includesPaths")
	private List<String> includesPath;
	@XmlElement
	@XmlElementWrapper
	private List<Symbol> symbols;

	public ASTTranslationUnitConfig(){
		includesPath=new ArrayList<String>();
		symbols=new ArrayList<Symbol>();
	}

	public String getFilePath(){
		return filePath;
	}

	public void setFilePath(String f){
		filePath=f;
	}

	public List<String> getIncludesPath(){
		return includesPath;
	}

	public void setIncludesPath(List<String> i){
		includesPath=i;
	}

	public List<Symbol> getSymbols(){
		return symbols;
	}

	public void setSymbols(List<Symbol> i){
		symbols=i;
	}

	public Map<String,String> getMapSymbols(){
		Map<String,String> m=new HashMap<String,String>();
		for (Symbol s : symbols){
			m.put(s.getKey(),s.getValue());
		}
		return m;
	}

	public static class Symbol{
		private String key;
		private String value;

		public Symbol(){
		}

		public String getKey(){
			return key;
		}

		public void setKey(String k){
			key=k;
		}

		public String getValue(){
			return value;
		}

		public void setValue(String v){
			value=v;
		}
	}


	private static JAXBContext context;
	static{
		try{
			context=JAXBContext.newInstance(ASTTranslationUnitConfig.class);
		}catch(Exception e){
			e.printStackTrace();
		}
	}

	public void writeTo(OutputStream out) throws Exception{
		Marshaller m=context.createMarshaller();
		m.marshal(this,out);
	}

	public static ASTTranslationUnitConfig readFrom(InputStream in) throws Exception{
		Unmarshaller um=context.createUnmarshaller();
		return (ASTTranslationUnitConfig)um.unmarshal(in);
	}
}
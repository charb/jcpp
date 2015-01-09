package jcpp.model.cpp.ast.macro;

import jcpp.model.cpp.ast.*;
import jcpp.model.cpp.ast.name.*;
import org.eclipse.cdt.core.dom.ast.*;
import javax.xml.bind.annotation.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTPreprocessorIncludeStatement extends ASTPreprocessorStatement{
	@XmlElement
	private long includedFileContentHash;
	@XmlElement
	private long includedFileReadTime;
	@XmlElement
	private long includedFileSize;
	@XmlElement
	private long includedFileTimestamp;
	@XmlElement
	private ASTNodeWrapper<ASTName> name;
	@XmlElement
	private String path;
	@XmlElement
	private boolean bIsActive;
	@XmlElement
	private boolean bIsErrorInIncludedFile;
	@XmlElement
	private boolean bIsIncludedFileExported;
	@XmlElement
	private boolean bIsResolved;
	@XmlElement
	private boolean bIsResolvedByHeuristics;
	@XmlElement
	private boolean bIsSystemInclude;

	public ASTPreprocessorIncludeStatement(IASTPreprocessorIncludeStatement p) throws Exception{
		super(p);
		includedFileContentHash=p.getIncludedFileContentsHash();
		includedFileReadTime=p.getIncludedFileReadTime();
		includedFileSize=p.getIncludedFileSize();
		includedFileTimestamp=p.getIncludedFileTimestamp();
		name=new ASTNodeWrapper<ASTName>();
		if (p.getName()!=null){
			name.set(ASTNameFactory.create(p.getName()));
		}
		path=p.getPath();
		bIsActive=p.isActive();
		bIsErrorInIncludedFile=p.isErrorInIncludedFile();
		bIsIncludedFileExported=p.isIncludedFileExported();
		bIsResolved=p.isResolved();
		bIsResolvedByHeuristics=p.isResolvedByHeuristics();
		bIsSystemInclude=p.isSystemInclude();
	}

	public ASTPreprocessorIncludeStatement(){
		name=new ASTNodeWrapper<ASTName>();
	}

	public long getIncludedFileContentHash(){
		return includedFileContentHash;
	}

	public void setIncludedFileContentHash(long c){
		includedFileContentHash=c;
	}

	public long getIncludedFileReadTime(){
		return includedFileReadTime;
	}

	public void setIncludedFileReadTime(long c){
		includedFileReadTime=c;
	}

	public long getIncludedFileSize(){
		return includedFileSize;
	}

	public void setIncludedFileSize(long c){
		includedFileSize=c;
	}

	public long getIncludedFileTimestamp(){
		return includedFileTimestamp;
	}

	public void setIncludedFileTimestamp(long c){
		includedFileTimestamp=c;
	}	

	public ASTName getName(){
		return name.get();
	}

	public void setName(ASTName c){
		name.set(c);
	}

	public String getPath(){
		return path;
	}

	public void setPath(String c){
		path=c;
	}

	public boolean isActive(){
		return bIsActive;
	}

	public void setIsActive(boolean b){
		bIsActive=b;
	}

	public boolean isErrorInIncludedFile(){
		return bIsErrorInIncludedFile;
	}

	public void setIsErrorInIncludedFile(boolean b){
		bIsErrorInIncludedFile=b;
	}

	public boolean isIncludedFileExported(){
		return bIsIncludedFileExported;
	}

	public void setIsIncludedFileExported(boolean b){
		bIsIncludedFileExported=b;
	}

	public boolean isResolved(){
		return bIsResolved;
	}

	public void setIsResolved(boolean b){
		bIsResolved=b;
	}

	public boolean isResolvedByHeuristics(){
		return bIsResolvedByHeuristics;
	}

	public void setIsResolvedByHeuristics(boolean b){
		bIsResolvedByHeuristics=b;
	}

	public boolean isSystemInclude(){
		return bIsSystemInclude;
	}

	public void setIsSystemInclude(boolean b){
		bIsSystemInclude=b;
	}
}
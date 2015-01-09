package jcpp.model.cpp.ast;

import org.eclipse.cdt.core.dom.ast.*;
import jcpp.model.cpp.ast.location.*;
import jcpp.model.cpp.ast.declaration.*;
import jcpp.model.cpp.ast.macro.*;
import jcpp.model.cpp.ast.stmt.*;
import java.util.*;
import java.io.*;
import javax.xml.bind.annotation.*;
import javax.xml.bind.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class ASTTranslationUnit extends ASTNode{
	@XmlElement
	private boolean bIsHeaderUnit;
	@XmlElement
	private String filePath;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTPreprocessorStatement> allPreprocessorStatements;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTComment> comments;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTDeclaration> declarations;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTPreprocessorIncludeStatement> includeDirectives;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTPreprocessorMacroDefinition> macroDefinitions;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTPreprocessorMacroDefinition> builtinMacroDefinitions;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTPreprocessorMacroExpansion> macroExpansions;
	@XmlElementRef
	@XmlElementWrapper
	private List<ASTNode> preprocessorProblems;
	
	public ASTTranslationUnit(IASTTranslationUnit node) throws Exception{
		allPreprocessorStatements=new ArrayList<ASTPreprocessorStatement>();
		if (node.getAllPreprocessorStatements()!=null){
			for (IASTPreprocessorStatement s : node.getAllPreprocessorStatements()){
				if (s!=null){
					allPreprocessorStatements.add(ASTPreprocessorStatementFactory.create(s));
				}
			}
		}

		comments=new ArrayList<ASTComment>();
		if (node.getComments()!=null){
			for (IASTComment s : node.getComments()){
				comments.add(new ASTComment(s));
			}
		}

		declarations=new ArrayList<ASTDeclaration>();
		if (node.getDeclarations()!=null){
			for (IASTDeclaration s : node.getDeclarations()){
				declarations.add((ASTDeclaration)ASTDeclarationFactory.create(s));
			}
		}

		filePath=node.getFilePath();

		includeDirectives=new ArrayList<ASTPreprocessorIncludeStatement>();
		if (node.getIncludeDirectives()!=null){
			for (IASTPreprocessorIncludeStatement s : node.getIncludeDirectives()){
				includeDirectives.add(new ASTPreprocessorIncludeStatement(s));
			}
		}

		macroDefinitions=new ArrayList<ASTPreprocessorMacroDefinition>();
		if (node.getMacroDefinitions()!=null){
			for (IASTPreprocessorMacroDefinition s : node.getMacroDefinitions()){
				macroDefinitions.add(new ASTPreprocessorMacroDefinition(s));
			}
		}

		builtinMacroDefinitions=new ArrayList<ASTPreprocessorMacroDefinition>();
		if (node.getBuiltinMacroDefinitions()!=null){
			for (IASTPreprocessorMacroDefinition s : node.getBuiltinMacroDefinitions()){
				builtinMacroDefinitions.add(new ASTPreprocessorMacroDefinition(s));
			}
		}

		macroExpansions=new ArrayList<ASTPreprocessorMacroExpansion>();
		if (node.getMacroExpansions()!=null){
			for (IASTPreprocessorMacroExpansion s : node.getMacroExpansions()){
				macroExpansions.add(new ASTPreprocessorMacroExpansion(s));
			}
		}

		preprocessorProblems=new ArrayList<ASTNode>();
		if (node.getPreprocessorProblems()!=null){
			for (IASTNode s : node.getPreprocessorProblems()){
				preprocessorProblems.add(ASTNodeFactory.create(s));
			}
		}

		bIsHeaderUnit=node.isHeaderUnit();
	}

	public ASTTranslationUnit(){
	}

	public void keepUnderPath(){
		File f=new File(filePath);
		for (Iterator<ASTDeclaration> it = getDeclarations().iterator();it.hasNext();){
            ASTDeclaration di=it.next();
            if (!f.equals(new File(di.getContainingFilename()))){
                it.remove();
            }
        }

        for (Iterator<ASTPreprocessorStatement> it = allPreprocessorStatements.iterator();it.hasNext();){
            ASTPreprocessorStatement di=it.next();
            if (!f.equals(new File(di.getContainingFilename()))){
                it.remove();
            }
        }

        for (Iterator<ASTComment> it = comments.iterator();it.hasNext();){
            ASTComment di=it.next();
            if (!f.equals(new File(di.getContainingFilename()))){
                it.remove();
            }
        }

        for (Iterator<ASTPreprocessorIncludeStatement> it = includeDirectives.iterator();it.hasNext();){
            ASTPreprocessorIncludeStatement di=it.next();
            if (!f.equals(new File(di.getContainingFilename()))){
                it.remove();
            }
        }

        for (Iterator<ASTPreprocessorMacroDefinition> it = macroDefinitions.iterator();it.hasNext();){
            ASTPreprocessorMacroDefinition di=it.next();
            if (!f.equals(new File(di.getContainingFilename()))){
                it.remove();
            }
        }

        for (Iterator<ASTPreprocessorMacroDefinition> it = builtinMacroDefinitions.iterator();it.hasNext();){
            ASTPreprocessorMacroDefinition di=it.next();
            if (!f.equals(new File(di.getContainingFilename()))){
                it.remove();
            }
        }

        for (Iterator<ASTPreprocessorMacroExpansion> it = macroExpansions.iterator();it.hasNext();){
            ASTPreprocessorMacroExpansion di=it.next();
            if (!f.equals(new File(di.getContainingFilename()))){
                it.remove();
            }
        }
	}

	public List<ASTPreprocessorStatement> getAllPreprocessorStatements(){
		return allPreprocessorStatements;
	}

	public void addPreprocessorStatement(ASTPreprocessorStatement s){
		allPreprocessorStatements.add(s);
	}

	public List<ASTComment> getComments(){
		return comments;
	}

	public void addComment(ASTComment s){
		comments.add(s);
	}

	public List<ASTDeclaration> getDeclarations(){
		return declarations;
	}

	public void addDeclaration(ASTDeclaration s){
		declarations.add(s);
	}

	public String getFilePath(){
		return filePath;
	}

	public void setFilePath(String s){
		filePath=s;
	}

	public List<ASTPreprocessorIncludeStatement> getIncludeDirectives(){
		return includeDirectives;
	}

	public void addIncludeDirective(ASTPreprocessorIncludeStatement s){
		includeDirectives.add(s);
	}

	public List<ASTPreprocessorMacroDefinition> getMacroDefinitions(){
		return macroDefinitions;
	}

	public void addMacroDefinition(ASTPreprocessorMacroDefinition s){
		macroDefinitions.add(s);
	}

	public List<ASTPreprocessorMacroDefinition> getBuiltinMacroDefinitions(){
		return builtinMacroDefinitions;
	}

	public void addBuiltinMacroDefinition(ASTPreprocessorMacroDefinition s){
		builtinMacroDefinitions.add(s);
	}

	public List<ASTPreprocessorMacroExpansion> getMacroExpansions(){
		return macroExpansions;
	}

	public void addMacroExpansion(ASTPreprocessorMacroExpansion s){
		macroExpansions.add(s);
	}

	public List<ASTNode> getPreprocessorProblems(){
		return preprocessorProblems;
	}

	public void addPreprocessorProblem(ASTNode s){
		preprocessorProblems.add(s);
	}

	public boolean isHeaderUnit(){
		return bIsHeaderUnit;
	}

	public void setHeaderUnit(boolean b){
		bIsHeaderUnit=b;
	}

	private static JAXBContext context;
	static{
		try{
			context=JAXBContext.newInstance(ASTNodeFactory.getClasses().toArray(new Class[0]));
		}catch(Exception e){
			e.printStackTrace();
		}
	}

	public void writeTo(OutputStream out) throws Exception{
		Marshaller m=context.createMarshaller();
		m.marshal(this,out);
	}

	public static ASTTranslationUnit readFrom(InputStream in) throws Exception{
		Unmarshaller um=context.createUnmarshaller();
		return (ASTTranslationUnit)um.unmarshal(in);
	}
}
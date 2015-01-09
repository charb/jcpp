package jcpp.converter.writer;

import jcpp.converter.model.*;
import jcpp.converter.strategies.*;
import java.io.*;
import java.util.*;

public class CPPClassHeaderWriter{
	protected IStrategies strategies;
	protected CPPClass clazz;
	protected CPPTypeWriter typeWriter;

	public CPPClassHeaderWriter(IStrategies strategies,CPPClass clazz){
		this.strategies=strategies;
		this.clazz=clazz;
		this.typeWriter=new CPPTypeWriter(strategies);
	}

	public void write(File currentDir) throws Exception{
		File headerFile=new File(currentDir,clazz.getHeader().getCPPFileName());
		headerFile.getParentFile().mkdirs();
		headerFile.createNewFile();

		StringBuffer sb=new StringBuffer();
		writeIfnDef(sb);
		writeIncludes(sb);
		writeUsingNamespace(sb);

		String idnt=writeStartNamespace(sb);

		writeBody(idnt,sb);

		writeEndNamespace(sb);
		writeEndIf(sb);

		FileOutputStream fos=new FileOutputStream(headerFile);
		fos.write(sb.toString().getBytes());
		fos.close();
	}

	protected void writeIfnDef(StringBuffer sb){
		sb.append("#ifndef ").append(clazz.getHeader().getIfDefName()).append(System.lineSeparator());
		sb.append("#define ").append(clazz.getHeader().getIfDefName()).append(System.lineSeparator());
		sb.append(System.lineSeparator());
	}

	protected void writeIncludes(StringBuffer sb){
		if (clazz.getHeader().getIncludes().size()>0){
			boolean done=false;
			for (CPPType type : clazz.getHeader().getIncludes()){
				done=true;
				sb.append("#include \"").append(type.getIncludePath()).append("\"").append(System.lineSeparator());
			}
			if (done){
				sb.append(System.lineSeparator());
			}
		}
	}

	protected void writeUsingNamespace(StringBuffer sb){
		if (clazz.getHeader().getUsings().size()>0){
			boolean done=false;
			for (CPPType type : clazz.getHeader().getUsings()){
				done=true;
				sb.append("using namespace ").append(type.getUsingNamespace()).append(";").append(System.lineSeparator());
			}
			if (done){
				sb.append(System.lineSeparator());
			}
		}
	}

	protected String writeStartNamespace(StringBuffer sb){
		String indnt="";
		for (String ns : clazz.getNamespaces()){
			sb.append(indnt+"namespace "+ns+"{").append(System.lineSeparator());
			indnt+="    ";
		}
		return indnt;
	}

	protected void writeBody(String ident,StringBuffer sb) throws Exception{
		sb.append(ident).append("class ").append(strategies.getClassBuilderStrategy().getMacroExport()).append(" ").append(clazz.getName()).append(" : ");
		sb.append(" public ").append(clazz.getSuperClass().getName());
		for (CPPType i : clazz.getInterfaces()) {
			sb.append(", public ").append(i.getName());
		}
		sb.append("{").append(System.lineSeparator());

        writeProtectedBody(ident,sb);
        writePublicBody(ident,sb);

        writeDestructor(ident,sb);
        sb.append(ident).append("};");
        sb.append(System.lineSeparator());
    }

    protected void writeProtected(String ident,StringBuffer sb) throws Exception{
    	sb.append(ident).append("protected:").append(System.lineSeparator());
    }

    protected void writeProtectedBody(String ident,StringBuffer sb) throws Exception{
    	boolean first=true;

    	if (clazz.getFields().size()>0){
    		boolean done=false;
			for (CPPField field : clazz.getFields().values()){
				if (field.isProtected()){
					done=true;
					if (first){
						writeProtected(ident,sb);
						first=false;
					}
					sb.append(ident).append("    ");
					if (field.isStatic()){
						sb.append("static ");
					}
					typeWriter.write(field.getType(),sb);
					sb.append(" ").append(field.getName()).append(";");
					sb.append(System.lineSeparator());
				}
			}
			if (done){
				sb.append(System.lineSeparator());
			}
		}

		if (clazz.getHeader().getMethods().size()>0){
			boolean done=false;
			for (CPPMethodInfo mi : clazz.getHeader().getMethods().values()){
				if (mi.isProtected()){
					done=true;
					if (first){
						writeProtected(ident,sb);
						first=false;
					}
					sb.append(ident).append("    ");
					if (!mi.isConstructor()){
						sb.append("virtual ");
						typeWriter.write(mi.getReturnType(),sb);
						sb.append(" ");
					}
					sb.append(mi.getName()).append("(");
					int i=0;
					for (CPPType type : mi.getParameters()){
						if (i>0){
							sb.append(", ");
						}
						typeWriter.write(type,sb);
						if (mi.getParameterNames().size()>0){
							sb.append(" ").append(mi.getParameterNames().get(i));
						}else{
							sb.append(" p"+i);
						}
						i++;
					}
					sb.append(");");
					sb.append(System.lineSeparator());
				}
			}
			if (done){
				sb.append(System.lineSeparator());
			}
		}
    }

    protected void writePublic(String ident,StringBuffer sb) throws Exception{
    	sb.append(ident).append("public:").append(System.lineSeparator());
    }

    protected void writePublicBody(String ident,StringBuffer sb) throws Exception{
    	boolean first=true;

    	if (clazz.getFields().size()>0){
    		boolean done=false;
			for (CPPField field : clazz.getFields().values()){
				if (!field.isProtected()){
					done=true;
					if (first){
						writePublic(ident,sb);
						first=false;
					}
					sb.append(ident).append("    ");
					if (field.isStatic()){
						sb.append("static ");
					}
					typeWriter.write(field.getType(),sb);
					sb.append(" ").append(field.getName()).append(";");
					sb.append(System.lineSeparator());
				}
			}
			if (done){
				sb.append(System.lineSeparator());
			}
		}

		if (clazz.getHeader().getMethods().size()>0){
			boolean done=false;
			for (CPPMethodInfo mi : clazz.getHeader().getMethods().values()){
				if (!mi.isProtected()){
					done=true;
					if (first){
						writePublic(ident,sb);
						first=false;
					}
					sb.append(ident).append("    ");
					if (!mi.isConstructor()){
						sb.append("virtual ");
						typeWriter.write(mi.getReturnType(),sb);
						sb.append(" ");
					}
					sb.append(mi.getName()).append("(");
					int i=0;
					for (CPPType type : mi.getParameters()){
						if (i>0){
							sb.append(", ");
						}
						typeWriter.write(type,sb);
						if (mi.getParameterNames().size()>0){
							sb.append(" ").append(mi.getParameterNames().get(i));
						}else{
							sb.append(" p"+i);
						}
						i++;
					}
					sb.append(");");
					sb.append(System.lineSeparator());
				}
			}
			if (done){
				sb.append(System.lineSeparator());
			}
		}
    }

    protected void writeDestructor(String ident,StringBuffer sb) throws Exception{
    	//TODO should be declared in MethodInfo
        sb.append(ident).append("    virtual").append(" ~").append(clazz.getName()).append("();");
        sb.append(System.lineSeparator());
    }

	protected void writeEndNamespace(StringBuffer sb){
		for (int i=clazz.getNamespaces().size() ; i>0 ; i--){
			String indnt="";
			for (int j=0;j<i-1;j++){
				indnt+="    ";
			}
			sb.append(indnt+"}").append(System.lineSeparator());
		}
	}

	protected void writeEndIf(StringBuffer sb){
		sb.append("#endif").append(System.lineSeparator());
	}
}
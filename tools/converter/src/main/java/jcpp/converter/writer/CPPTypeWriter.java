package jcpp.converter.writer;

import jcpp.converter.model.*;
import jcpp.converter.strategies.*;
import java.io.*;
import java.util.*;

public class CPPTypeWriter{
	protected IStrategies strategies;

	public CPPTypeWriter(IStrategies strategies){
		this.strategies=strategies;
	}

	public void write(CPPType type, StringBuffer sb) throws Exception{
		if (!type.isPrimitive()){
			sb.append(type.getName()+"*");
		}else{
			sb.append(type.getName());
		}
    }

	public void writeClazz(CPPType type, StringBuffer sb) throws Exception{
		if (!type.isPrimitive()){
			sb.append(type.getName()).append("::getClazz()");
		}else{
			throw new Exception("TODO type=="+type);
		}
    }
}
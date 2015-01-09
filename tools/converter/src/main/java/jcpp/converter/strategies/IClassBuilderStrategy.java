package jcpp.converter.strategies;

import jcpp.converter.model.*;
import java.util.*;
import org.objectweb.asm.*;

public interface IClassBuilderStrategy{

	public String getMacroExport();

	public void initialize(CPPClass clazz);

	public CPPType getCPPType(Type type);

	public CPPType getCPPType(String type);
}
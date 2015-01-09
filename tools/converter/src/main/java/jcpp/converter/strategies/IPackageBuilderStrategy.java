package jcpp.converter.strategies;

import jcpp.converter.model.*;
import java.util.*;
import java.io.*;

public interface IPackageBuilderStrategy{

	public void initialize(CPPPackage pkge);

	public boolean skipFile(File fileName);

	public boolean skipFolder(File fileName);
}
package jcpp.converter.strategies;

import jcpp.converter.model.*;

public interface IStrategies{

	public IPackageBuilderStrategy getPackageBuilderStrategy();

	public IClassBuilderStrategy getClassBuilderStrategy();
}
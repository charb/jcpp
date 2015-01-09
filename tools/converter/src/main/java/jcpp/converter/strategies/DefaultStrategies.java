package jcpp.converter.strategies;

import jcpp.converter.model.*;

public class DefaultStrategies implements IStrategies{
	protected IPackageBuilderStrategy packageBuilderStrategy;
	protected IClassBuilderStrategy classBuilderStrategy;

	public DefaultStrategies(){
		packageBuilderStrategy=new DefaultPackageBuilderStrategy();
		classBuilderStrategy=new DefaultClassBuilderStrategy();
	}

	public IPackageBuilderStrategy getPackageBuilderStrategy(){
		return packageBuilderStrategy;
	}

	public IClassBuilderStrategy getClassBuilderStrategy(){
		return classBuilderStrategy;
	}
}
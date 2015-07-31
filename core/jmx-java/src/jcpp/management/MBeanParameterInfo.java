package jcpp.management;

public class MBeanParameterInfo extends MBeanFeatureInfo implements Cloneable {

	static final long serialVersionUID = 7432616882776782338L;
	
	static final MBeanParameterInfo[] NO_PARAMS = new MBeanParameterInfo[0];

	
	public MBeanParameterInfo(String name, String description) {
		super(name, description);
	}

}

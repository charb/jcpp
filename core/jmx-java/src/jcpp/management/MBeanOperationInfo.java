package jcpp.management;

import java.lang.annotation.Annotation;
import java.lang.reflect.Method;

import jcpp.jmx.mbeanserver.Introspector;

public class MBeanOperationInfo extends MBeanFeatureInfo implements Cloneable {

	static final long serialVersionUID = -6178860474881375330L;

	public static final int INFO = 0;
	public static final int ACTION = 1;
	public static final int ACTION_INFO = 2;

	static final MBeanOperationInfo[] NO_OPERATIONS = new MBeanOperationInfo[0];

	public static final int UNKNOWN = 3;

	public MBeanOperationInfo(String description, Method method) {
		this(method.getName(), description, methodSignature(method), method.getReturnType().getName());
	}



	public MBeanOperationInfo(String name, String description, MBeanParameterInfo[] signature, String type) {

		super(name, description);

		if (signature == null || signature.length == 0)
			signature = MBeanParameterInfo.NO_PARAMS;
		else
			signature = signature.clone();
	}

	static MBeanParameterInfo[] parameters(Class[] classes, Annotation[][] annots) {
		final MBeanParameterInfo[] params = new MBeanParameterInfo[classes.length];
		assert (classes.length == annots.length);

		for (int i = 0; i < classes.length; i++) {
			
			final String pn = "p" + (i + 1);
			params[i] = new MBeanParameterInfo(pn, "");
		}

		return params;
	}

	private static MBeanParameterInfo[] methodSignature(Method method) {
		final Class[] classes = method.getParameterTypes();
		final Annotation[][] annots = method.getParameterAnnotations();
		return parameters(classes, annots);
	}

}

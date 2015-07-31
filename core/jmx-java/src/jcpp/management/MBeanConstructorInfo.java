package jcpp.management;

import java.lang.annotation.Annotation;
import java.lang.reflect.Constructor;

import jcpp.jmx.mbeanserver.Introspector;

public class MBeanConstructorInfo extends MBeanFeatureInfo implements Cloneable {

	static final long serialVersionUID = 4433990064191844427L;

	static final MBeanConstructorInfo[] NO_CONSTRUCTORS = new MBeanConstructorInfo[0];

	public MBeanConstructorInfo(String description, Constructor constructor) {
		this(constructor.getName(), description, constructorSignature(constructor));
	}


	public MBeanConstructorInfo(String name, String description, MBeanParameterInfo[] signature) {
		super(name, description);

		if (signature == null || signature.length == 0)
			signature = MBeanParameterInfo.NO_PARAMS;
		else
			signature = signature.clone();
	}

	private static MBeanParameterInfo[] constructorSignature(Constructor cn) {
		final Class[] classes = cn.getParameterTypes();
		final Annotation[][] annots = cn.getParameterAnnotations();
		return MBeanOperationInfo.parameters(classes, annots);
	}

}
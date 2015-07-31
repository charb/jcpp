package jcpp.management;

import java.lang.reflect.Method;

import jcpp.jmx.mbeanserver.Introspector;

public class MBeanAttributeInfo extends MBeanFeatureInfo implements Cloneable {

	private static final long serialVersionUID = 1452116342341778410L;

	private final boolean is;

	static final MBeanAttributeInfo[] NO_ATTRIBUTES = new MBeanAttributeInfo[0];


	public MBeanAttributeInfo(String name, String description, Method getter, Method setter) throws Exception {
		this(name, attributeType(getter, setter), description, (getter != null), (setter != null), isIs(getter));
	}

	public MBeanAttributeInfo(String name, String type, String description, boolean isReadable, boolean isWritable, boolean isIs) {
		super(name, description);

		if (isIs && !isReadable) {
			throw new IllegalArgumentException("Cannot have an \"is\" getter " + "for a non-readable attribute");
		}
		if (isIs && !type.equals("java.lang.Boolean") && !type.equals("boolean")) {
			throw new IllegalArgumentException("Cannot have an \"is\" getter " + "for a non-boolean attribute");
		}
		this.is = isIs;
	}

	public boolean isIs() {
		return is;
	}

	private static boolean isIs(Method getter) {
		return (getter != null && getter.getName().startsWith("is") && (getter.getReturnType().equals(Boolean.TYPE) || getter.getReturnType().equals(Boolean.class)));
	}

	private static String attributeType(Method getter, Method setter) throws Exception {
		Class type = null;

		if (getter != null) {
			if (getter.getParameterTypes().length != 0) {
				throw new Exception("bad getter arg count");
			}
			type = getter.getReturnType();
			if (type == Void.TYPE) {
				throw new Exception("getter " + getter.getName() + " returns void");
			}
		}

		if (setter != null) {
			Class params[] = setter.getParameterTypes();
			if (params.length != 1) {
				throw new Exception("bad setter arg count");
			}
			if (type == null)
				type = params[0];
			else if (type != params[0]) {
				throw new Exception("type mismatch between " + "getter and setter");
			}
		}

		if (type == null) {
			throw new Exception("getter and setter cannot " + "both be null");
		}

		return type.getName();
	}

}

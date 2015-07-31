package jcpp.management;

import java.io.Serializable;




public class MBeanInfo implements Serializable, Cloneable {

	static final long serialVersionUID = -6451021435135161911L;

	private final String className;

	private final String description;

	private final MBeanAttributeInfo[] attributes;

	private final MBeanOperationInfo[] operations;

	private final MBeanConstructorInfo[] constructors;



	public MBeanInfo(String className, String description, MBeanAttributeInfo[] attributes, MBeanConstructorInfo[] constructors, MBeanOperationInfo[] operations) throws IllegalArgumentException {

		this.className = className;

		this.description = description;

		if (attributes == null)
			attributes = MBeanAttributeInfo.NO_ATTRIBUTES;
		this.attributes = attributes;

		if (operations == null)
			operations = MBeanOperationInfo.NO_OPERATIONS;
		this.operations = operations;

		if (constructors == null)
			constructors = MBeanConstructorInfo.NO_CONSTRUCTORS;
		this.constructors = constructors;

	}

	

	public String getDescription() {
		return description;
	}

	public MBeanAttributeInfo[] getAttributes() {
		MBeanAttributeInfo[] as = nonNullAttributes();
		if (as.length == 0)
			return as;
		else
			return as.clone();
	}

	public MBeanOperationInfo[] getOperations() {
		MBeanOperationInfo[] os = nonNullOperations();
		if (os.length == 0)
			return os;
		else
			return os.clone();
	}

	public MBeanConstructorInfo[] getConstructors() {
		MBeanConstructorInfo[] cs = nonNullConstructors();
		if (cs.length == 0)
			return cs;
		else
			return cs.clone();
	}

	public String getClassName() {
		return className;
	}

	private MBeanConstructorInfo[] nonNullConstructors() {
		return (constructors == null) ? MBeanConstructorInfo.NO_CONSTRUCTORS : constructors;
	}

	private MBeanOperationInfo[] nonNullOperations() {
		return (operations == null) ? MBeanOperationInfo.NO_OPERATIONS : operations;
	}

	private MBeanAttributeInfo[] nonNullAttributes() {
		return (attributes == null) ? MBeanAttributeInfo.NO_ATTRIBUTES : attributes;
	}
}

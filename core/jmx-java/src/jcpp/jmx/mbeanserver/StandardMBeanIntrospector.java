package jcpp.jmx.mbeanserver;

import java.lang.reflect.Method;
import java.lang.reflect.Type;
import java.util.WeakHashMap;


import jcpp.management.MBeanAttributeInfo;
import jcpp.management.MBeanOperationInfo;

public class StandardMBeanIntrospector extends MBeanIntrospector<Method> {

	private static final StandardMBeanIntrospector instance = new StandardMBeanIntrospector();

	private static final PerInterfaceMap<Method> perInterfaceMap = new PerInterfaceMap<Method>();

	private static final MBeanInfoMap mbeanInfoMap = new MBeanInfoMap();

	static StandardMBeanIntrospector getInstance() {
		return instance;
	}

	@Override
	jcpp.jmx.mbeanserver.MBeanIntrospector.PerInterfaceMap<Method> getPerInterfaceMap() {
		return perInterfaceMap;
	}

	@Override
	MBeanAnalyzer<Method> getAnalyzer(Class<?> mbeanInterface) throws Exception {
		return MBeanAnalyzer.analyzer(mbeanInterface, this);
	}

	@Override
	String[] getSignature(Method m) {
		Class<?>[] params = m.getParameterTypes();
		String[] sig = new String[params.length];
		for (int i = 0; i < params.length; i++)
			sig[i] = params[i].getName();
		return sig;
	}

	@Override
	void checkMethod(Method m) throws IllegalArgumentException {
		// TODO Auto-generated method stub
		System.out.println("empty " + this.getClass().getName());
	}

	

	@Override
	jcpp.jmx.mbeanserver.MBeanIntrospector.MBeanInfoMap getMBeanInfoMap() {
		return mbeanInfoMap;
	}


	@Override
	Method mFrom(Method m) {
		return m;
	}

	@Override
	Type getGenericReturnType(Method m) {
		return m.getGenericReturnType();
	}

	@Override
	Type[] getGenericParameterTypes(Method m) {
		return m.getGenericParameterTypes();
	}



	@Override
	MBeanAttributeInfo getMBeanAttributeInfo(String attributeName,
			Method getter, Method setter) {
		final String description = "Attribute exposed for management";
		try {
			return new MBeanAttributeInfo(attributeName, description, getter,
					setter);
		} catch (Exception e) {
			throw new RuntimeException(e); // should not happen
		}
	}

	@Override
	MBeanOperationInfo getMBeanOperationInfo(String operationName,
			Method operation) {
		final String description = "Operation exposed for management";
		return new MBeanOperationInfo(description, operation);
	}


	@Override
	String getName(Method m) {
		// TODO Auto-generated method stub
		System.out.println("14--->> implement me " + this.getClass().getName());
		return null;
	}

	@Override
	Object invokeM2(Method m, Object target, Object[] args, Object cookie)
			throws Exception {
		return m.invoke(target, args);
	}

}

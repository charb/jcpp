package jcpp.jmx.mbeanserver;

import java.lang.reflect.Method;
import java.lang.reflect.Type;


public class StandardMBeanIntrospector extends MBeanIntrospector<Method> {

	private static final StandardMBeanIntrospector instance = new StandardMBeanIntrospector();

	private static final PerInterfaceMap<Method> perInterfaceMap = new PerInterfaceMap<Method>();


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

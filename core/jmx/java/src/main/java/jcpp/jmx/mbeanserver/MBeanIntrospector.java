package jcpp.jmx.mbeanserver;



import java.lang.reflect.Method;
import java.lang.reflect.Type;
import java.util.HashMap;



abstract class MBeanIntrospector<M> {

	static final class PerInterfaceMap<M> extends HashMap<Class<?>, PerInterface<M>> {

		/**
		 * 
		 */
		private static final long serialVersionUID = 1L;
	}


	
	abstract PerInterfaceMap<M> getPerInterfaceMap();

	abstract MBeanAnalyzer<M> getAnalyzer(Class<?> mbeanInterface) throws Exception;

	abstract String[] getSignature(M m);

	abstract void checkMethod(M m) throws IllegalArgumentException;

	abstract M mFrom(Method m);

	abstract String getName(M m);

	abstract Type getGenericReturnType(M m);

	abstract Type[] getGenericParameterTypes(M m);

	abstract Object invokeM2(M m, Object target, Object[] args, Object cookie) throws Exception;

	
	
	final PerInterface<M> getPerInterface(Class<?> mbeanInterface) throws Exception {
		PerInterfaceMap<M> map = getPerInterfaceMap();
		synchronized (map) {
			PerInterface<M> pi = map.get(mbeanInterface);
			
			if (pi == null) {
				try {
					MBeanAnalyzer<M> analyzer = getAnalyzer(mbeanInterface);
					pi = new PerInterface<M>(mbeanInterface, this, analyzer);	
					map.put(mbeanInterface, pi);
				} catch (Exception x) {
					throw Introspector.throwException(mbeanInterface, x);
				}
			}
			return pi;
		}
	}

	final boolean consistent(M getter, M setter) {
		return (getter == null || setter == null || getGenericReturnType(getter).equals(getGenericParameterTypes(setter)[0]));
	}

	final Object invokeM(M m, Object target, Object[] args, Object cookie) throws Exception {
		try {
			return invokeM2(m, target, args, cookie);
		} catch (Exception e) {
			throw new Exception(e); // not reached
		}
	}

	final void invokeSetter(String name, M setter, Object target, Object arg, Object cookie) throws Exception {
		try {
			invokeM2(setter, target, new Object[] { arg }, cookie);
		} catch (Exception e) {
			throw new Exception();
		}
	}

	
}

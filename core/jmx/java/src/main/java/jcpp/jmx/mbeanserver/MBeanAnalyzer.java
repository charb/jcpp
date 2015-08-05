package jcpp.jmx.mbeanserver;

import java.lang.reflect.Method;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;
import java.util.Map;
import java.util.Set;

import static jcpp.jmx.mbeanserver.Util.*;

class MBeanAnalyzer<M> {

	public interface MBeanVisitor<M> {
		public void visitAttribute(String attributeName, M getter, M setter);

		public void visitOperation(String operationName, M operattion);
	}

	private static class MethodOrder implements Comparator<Method> {
		public int compare(Method a, Method b) {
			final int cmp = a.getName().compareTo(b.getName());
			if (cmp != 0)
				return cmp;
			final Class<?>[] aparams = a.getParameterTypes();
			final Class<?>[] bparams = b.getParameterTypes();
			if (aparams.length != bparams.length)
				return aparams.length - bparams.length;
			if (!Arrays.equals(aparams, bparams)) {
				return Arrays.toString(aparams).compareTo(Arrays.toString(bparams));
			}
			final Class<?> aret = a.getReturnType();
			final Class<?> bret = b.getReturnType();
			if (aret == bret)
				return 0;

			// Super type comes first: Object, Number, Integer
			if (aret.isAssignableFrom(bret))
				return -1;
			return +1; // could assert bret.isAssignableFrom(aret)
		}

		public final static MethodOrder instance = new MethodOrder();
	}

	private static class AttrMethods<M> {
		M getter;
		M setter;
	}

	private Map<String, List<M>> opMap = newInsertionOrderMap();

	private Map<String, AttrMethods<M>> attrMap = newInsertionOrderMap();

	
	
	private MBeanAnalyzer(Class<?> mbeanInterface, MBeanIntrospector<M> introspector) throws Exception {
		if (!mbeanInterface.isInterface()) {
			throw new Exception("Not an interface: " + mbeanInterface.getName());
		}

		try {
			initMaps(mbeanInterface, introspector);
		} catch (Exception x) {
			throw Introspector.throwException(mbeanInterface, x);
		}
	}

	void visit(MBeanVisitor<M> visitor) {
		// visit attributes
		for (Map.Entry<String, AttrMethods<M>> entry : attrMap.entrySet()) {
			String name = entry.getKey();
			AttrMethods<M> am = entry.getValue();
			visitor.visitAttribute(name, am.getter, am.setter);
		}

		// visit operations
		for (Map.Entry<String, List<M>> entry : opMap.entrySet()) {
			for (M m : entry.getValue())
				visitor.visitOperation(entry.getKey(), m);
		}
	}

	private void initMaps(Class<?> mbeanInterface, MBeanIntrospector<M> introspector) throws Exception {
		final Method[] methodArray = mbeanInterface.getMethods();

		final List<Method> methods = eliminateCovariantMethods(methodArray);

		/*
		 * Run through the methods to detect inconsistencies and to enable us to
		 * give getter and setter together to visitAttribute.
		 */
		for (Method m : methods) {
			String name = m.getName();

			final M cm = introspector.mFrom(m);

			String attrName = "";
			if (name.startsWith("get"))
				attrName = name.substring(3);
			else if (name.startsWith("is") && m.getReturnType() == boolean.class)
				attrName = name.substring(2);

			if (attrName.length() != 0 && m.getParameterTypes().length == 0 && m.getReturnType() != void.class) {
				// It's a getter
				// Check we don't have both isX and getX
				AttrMethods<M> am = attrMap.get(attrName);
				if (am == null)
					am = new AttrMethods<M>();
				else {
					if (am.getter != null) {
						final String msg = "Attribute " + attrName + " has more than one getter";
						throw new Exception(msg);
					}
				}
				am.getter = cm;
				attrMap.put(attrName, am);
			} else if (name.startsWith("set") && name.length() > 3 && m.getParameterTypes().length == 1 && m.getReturnType() == void.class) {
				// It's a setter
				attrName = name.substring(3);
				AttrMethods<M> am = attrMap.get(attrName);
				if (am == null)
					am = new AttrMethods<M>();
				else if (am.setter != null) {
					final String msg = "Attribute " + attrName + " has more than one setter";
					throw new Exception(msg);
				}
				am.setter = cm;
				attrMap.put(attrName, am);
			} else {
				// It's an operation
				List<M> cms = opMap.get(name);
				if (cms == null)
					cms = newList();
				cms.add(cm);
				opMap.put(name, cms);
			}
		}
		/* Check that getters and setters are consistent. */
		for (Map.Entry<String, AttrMethods<M>> entry : attrMap.entrySet()) {
			AttrMethods<M> am = entry.getValue();
			if (!introspector.consistent(am.getter, am.setter)) {
				final String msg = "Getter and setter for " + entry.getKey() + " have inconsistent types";
				throw new Exception(msg);
			}
		}
	}

	static List<Method> eliminateCovariantMethods(Method[] methodArray) {
		// We are assuming that you never have very many methods with the
		// same name, so it is OK to use algorithms that are quadratic
		// in the number of methods with the same name.

		final int len = methodArray.length;
		final Method[] sorted = methodArray.clone();
		Arrays.sort(sorted, MethodOrder.instance);
		final Set<Method> overridden = newSet();
		for (int i = 1; i < len; i++) {
			final Method m0 = sorted[i - 1];
			final Method m1 = sorted[i];

			// Methods that don't have the same name can't override each others
			if (!m0.getName().equals(m1.getName()))
				continue;

			// Methods that have the same name and same signature override
			// each other. In that case, the second method overrides the first,
			// due to the way we have sorted them in MethodOrder.
			if (Arrays.equals(m0.getParameterTypes(), m1.getParameterTypes())) {
				overridden.add(m0);
			}
		}

		final List<Method> methods = newList(Arrays.asList(methodArray));
		methods.removeAll(overridden);
		return methods;
	}

	static <M> MBeanAnalyzer<M> analyzer(Class<?> mbeanInterface, MBeanIntrospector<M> introspector) throws Exception {
		return new MBeanAnalyzer<M>(mbeanInterface, introspector);
	}



}

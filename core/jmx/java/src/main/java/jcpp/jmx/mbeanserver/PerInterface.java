package jcpp.jmx.mbeanserver;

import static jcpp.jmx.mbeanserver.Util.newList;
import static jcpp.jmx.mbeanserver.Util.newMap;

import java.lang.reflect.Method;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Map;



final class PerInterface<M> {

	private final Class<?> mbeanInterface;

	private final MBeanIntrospector<M> introspector;

	private final Map<String, M> getters = newMap();
	private final Map<String, M> setters = newMap();
	private final Map<String, List<MethodAndSig>> ops = newMap();

	PerInterface(Class<?> mbeanInterface, MBeanIntrospector<M> introspector, MBeanAnalyzer<M> analyzer) {
		this.mbeanInterface = mbeanInterface;
		this.introspector = introspector;
		
		analyzer.visit(new InitMaps());
	}

	Class<?> getMBeanInterface() {
		return mbeanInterface;
	}



	Object invoke(Object resource, String operation, Object[] params, String[] signature, Object cookie) throws Exception {

		final List<MethodAndSig> list = ops.get(operation);
		if (list == null) {
			final String msg = "No such operation: " + operation;
		throw new Exception(msg);
		}
		if (signature == null)
			signature = new String[0];
		MethodAndSig found = null;
		for (MethodAndSig mas : list) {
			if (Arrays.equals(mas.signature, signature)) {
				found = mas;
				break;
			}
		}
		if (found == null) {
			final String badSig = sigString(signature);
			final String msg;
			if (list.size() == 1) { // helpful exception message
				msg = "Signature mismatch for operation " + operation + ": " + badSig + " should be " + sigString(list.get(0).signature);
			} else {
				msg = "Operation " + operation + " exists but not with " + "this signature: " + badSig;
			}
			throw new Exception(msg);
		}
		return introspector.invokeM(found.method, resource, params, cookie);
	}

	Object getAttribute(Object resource, String attribute, Object cookie) throws Exception {
		final M cm = getters.get(attribute);
		if (cm == null) {
			final String msg;
			if (setters.containsKey(attribute))
				msg = "Write-only attribute: " + attribute;
			else
				msg = "No such attribute: " + attribute;
			throw new Exception(msg);
		}
		return introspector.invokeM(cm, resource, (Object[]) null, cookie);
	}

	void setAttribute(Object resource, String attribute, Object value, Object cookie) throws Exception {
		final M cm = setters.get(attribute);
		
		if (cm == null) {
			final String msg;
			if (getters.containsKey(attribute))
				msg = "Read-only attribute: " + attribute;
			else
				msg = "No such attribute: " + attribute;
			throw new Exception(msg);
		}
		introspector.invokeSetter(attribute, cm, resource, value, cookie);
	}

	private class InitMaps implements MBeanAnalyzer.MBeanVisitor<M> {
		public void visitAttribute(String attributeName, M getter, M setter) {
			if (getter != null) {
				introspector.checkMethod(getter);
				final Object old = getters.put(attributeName, getter);
				assert (old == null);
			}
			if (setter != null) {
				introspector.checkMethod(setter);
				final Object old = setters.put(attributeName, setter);
				assert (old == null);
			}
		}

		public void visitOperation(String operationName, M operation) {
			introspector.checkMethod(operation);
			final String[] sig = introspector.getSignature(operation);
			final MethodAndSig mas = new MethodAndSig();
			mas.method = operation;
			mas.signature = sig;
			List<MethodAndSig> list = ops.get(operationName);
			if (list == null)
				list = Collections.singletonList(mas);
			else {
				if (list.size() == 1)
					list = newList(list);
				list.add(mas);
			}
			ops.put(operationName, list);
		}
	}



	private String sigString(String[] signature) {
		StringBuilder b = new StringBuilder("(");
		if (signature != null) {
			for (String s : signature) {
				if (b.length() > 1)
					b.append(", ");
				b.append(s);
			}
		}
		return b.append(")").toString();
	}

	private class MethodAndSig {
		M method;
		String[] signature;
	}

}

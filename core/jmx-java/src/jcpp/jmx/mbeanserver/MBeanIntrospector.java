package jcpp.jmx.mbeanserver;

import static jcpp.jmx.mbeanserver.Util.newList;

import java.lang.ref.WeakReference;
import java.lang.reflect.Constructor;
import java.lang.reflect.Method;
import java.lang.reflect.Type;
import java.util.List;
import java.util.WeakHashMap;



import jcpp.management.MBeanAttributeInfo;
import jcpp.management.MBeanConstructorInfo;
import jcpp.management.MBeanInfo;
import jcpp.management.MBeanOperationInfo;

abstract class MBeanIntrospector<M> {

	static final class PerInterfaceMap<M> extends WeakHashMap<Class<?>, WeakReference<PerInterface<M>>> {
	}

	abstract PerInterfaceMap<M> getPerInterfaceMap();

	abstract MBeanAnalyzer<M> getAnalyzer(Class<?> mbeanInterface) throws Exception;

	abstract String[] getSignature(M m);

	abstract void checkMethod(M m) throws IllegalArgumentException;


	abstract MBeanInfoMap getMBeanInfoMap();

	abstract M mFrom(Method m);

	abstract String getName(M m);

	abstract Type getGenericReturnType(M m);

	abstract Type[] getGenericParameterTypes(M m);

	abstract MBeanAttributeInfo getMBeanAttributeInfo(String attributeName, M getter, M setter);

	abstract MBeanOperationInfo getMBeanOperationInfo(String operationName, M operation);

	abstract Object invokeM2(M m, Object target, Object[] args, Object cookie) throws Exception;

	final PerInterface<M> getPerInterface(Class<?> mbeanInterface) throws Exception {
		PerInterfaceMap<M> map = getPerInterfaceMap();
		synchronized (map) {
			WeakReference<PerInterface<M>> wr = map.get(mbeanInterface);
			PerInterface<M> pi = (wr == null) ? null : wr.get();
			if (pi == null) {
				try {
					MBeanAnalyzer<M> analyzer = getAnalyzer(mbeanInterface);
					MBeanInfo mbeanInfo = makeInterfaceMBeanInfo(mbeanInterface, analyzer);
					pi = new PerInterface<M>(mbeanInterface, this, analyzer, mbeanInfo);
					wr = new WeakReference<PerInterface<M>>(pi);
					map.put(mbeanInterface, wr);
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

	private MBeanInfo makeInterfaceMBeanInfo(Class<?> mbeanInterface, MBeanAnalyzer<M> analyzer) {
		final MBeanInfoMaker maker = new MBeanInfoMaker();
		analyzer.visit(maker);
		final String description = "Information on the management interface of the MBean";
		return maker.makeMBeanInfo(mbeanInterface, description);
	}

	private class MBeanInfoMaker implements MBeanAnalyzer.MBeanVisitor<M> {

		private final List<MBeanAttributeInfo> attrs = newList();
		private final List<MBeanOperationInfo> ops = newList();

		MBeanInfo makeMBeanInfo(Class<?> mbeanInterface, String description) {
			final MBeanAttributeInfo[] attrArray = attrs.toArray(new MBeanAttributeInfo[0]);
			final MBeanOperationInfo[] opArray = ops.toArray(new MBeanOperationInfo[0]);
			return new MBeanInfo(mbeanInterface.getName(), description, attrArray, null, opArray);
		}

		@Override
		public void visitAttribute(String attributeName, M getter, M setter) {

			MBeanAttributeInfo mbai = getMBeanAttributeInfo(attributeName, getter, setter);
			attrs.add(mbai);
		}

		@Override
		public void visitOperation(String operationName, M operation) {
			MBeanOperationInfo mboi = getMBeanOperationInfo(operationName, operation);
			ops.add(mboi);
		}

	}

	final MBeanInfo getMBeanInfo(Object resource, PerInterface<M> perInterface) throws Exception {
		MBeanInfo mbi = getClassMBeanInfo(resource.getClass(), perInterface);
		return new MBeanInfo(mbi.getClassName(), mbi.getDescription(), mbi.getAttributes(), mbi.getConstructors(), mbi.getOperations());
	}



	static class MBeanInfoMap extends WeakHashMap<Class<?>, WeakHashMap<Class<?>, MBeanInfo>> {
	}

	final MBeanInfo getClassMBeanInfo(Class<?> resourceClass, PerInterface<M> perInterface) throws Exception {
		MBeanInfoMap map = getMBeanInfoMap();
		synchronized (map) {
			WeakHashMap<Class<?>, MBeanInfo> intfMap = map.get(resourceClass);
			if (intfMap == null) {
				intfMap = new WeakHashMap<Class<?>, MBeanInfo>();
				map.put(resourceClass, intfMap);
			}
			Class<?> intfClass = perInterface.getMBeanInterface();
			MBeanInfo mbi = intfMap.get(intfClass);
			if (mbi == null) {
				MBeanInfo imbi = perInterface.getMBeanInfo();
				mbi = new MBeanInfo(resourceClass.getName(), imbi.getDescription(), imbi.getAttributes(), findConstructors(resourceClass), imbi.getOperations());
				intfMap.put(intfClass, mbi);
			}
			return mbi;
		}
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

	private static MBeanConstructorInfo[] findConstructors(Class<?> c) {
		Constructor[] cons = c.getConstructors();
		MBeanConstructorInfo[] mbc = new MBeanConstructorInfo[cons.length];
		for (int i = 0; i < cons.length; i++) {
			final String descr = "Public constructor of the MBean";
			mbc[i] = new MBeanConstructorInfo(descr, cons[i]);
		}
		return mbc;
	}

}

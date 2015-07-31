package jcpp.management;

import java.util.ArrayList;

import jcpp.jmx.mbeanserver.MBeanServerDelegate;

public class MBeanServerFactory {

	private static MBeanServerBuilder builder = null;
	private static final ArrayList<MBeanServer> mBeanServerList = new ArrayList<MBeanServer>();

	public static MBeanServer createMBeanServer() {
		final MBeanServer mBeanServer = newMBeanServer();
		addMBeanServer(mBeanServer);
		return mBeanServer;
	}

	public static MBeanServer newMBeanServer() {
		// Get the builder. Creates a new one if necessary.
		//
		final MBeanServerBuilder mbsBuilder = getNewMBeanServerBuilder();
		// Returned value cannot be null. NullPointerException if violated.

		synchronized (mbsBuilder) {
			final MBeanServerDelegate delegate = mbsBuilder.newMBeanServerDelegate();
			if (delegate == null) {
				final String msg = "MBeanServerBuilder.newMBeanServerDelegate() " + "returned null";
				throw new RuntimeException(msg);
			}
			final MBeanServer mbeanServer = mbsBuilder.newMBeanServer(null, null, delegate);
			if (mbeanServer == null) {
				final String msg = "MBeanServerBuilder.newMBeanServer() returned null";
				throw new RuntimeException(msg);
			}
			return mbeanServer;
		}
	}

	private static synchronized void addMBeanServer(MBeanServer mbs) {
		mBeanServerList.add(mbs);
	}

	private static synchronized MBeanServerBuilder getNewMBeanServerBuilder() {
		checkMBeanServerBuilder();
		return builder;
	}

	private static synchronized void checkMBeanServerBuilder() {
		final Class newBuilderClass = MBeanServerBuilder.class;
		// Check whether a new builder needs to be created
		if (builder != null) {
			final Class builderClass = builder.getClass();
			if (newBuilderClass == builderClass)
				return; // no need to create a new builder...
		}
		// Create a new builder
		builder = newBuilder(newBuilderClass);
	}


	private static MBeanServerBuilder newBuilder(Class builderClass) {
		try {
			final Object builder = builderClass.newInstance();
			return (MBeanServerBuilder) builder;
		} catch (RuntimeException x) {
			throw x;
		} catch (Exception x) {
			final String msg = "Failed to instantiate a MBeanServerBuilder from " + builderClass + ": " + x;
			throw new RuntimeException(msg, x);
		}
	}

}

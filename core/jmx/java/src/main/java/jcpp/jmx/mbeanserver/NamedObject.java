package jcpp.jmx.mbeanserver;

import jcpp.management.DynamicMBean;

public class NamedObject {

	private final DynamicMBean object;

	public NamedObject(DynamicMBean object) {
		this.object = object;
	}


	public DynamicMBean getObject() {
		return object;
	}
}

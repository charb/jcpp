package jcpp.management;

import java.io.Serializable;

public class MBeanFeatureInfo implements Serializable {

	static final long serialVersionUID = 3952882688968447265L;

	private final String name;

	private final String description;


	public MBeanFeatureInfo(String name, String description) {
		this.name = name;
		this.description = description;
	}

	public String getName() {
		return name;
	}

	public String getDescription() {
		return description;
	}

}

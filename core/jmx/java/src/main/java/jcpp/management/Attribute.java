package jcpp.management;

import java.io.Serializable;


public class Attribute implements Serializable {

	private static final long serialVersionUID = 2484220110589082382L;
	
	private String name;
	private Object value = null;
	
	public Attribute(String name, Object value) {
		if(name == null)
			try {
				throw new Exception("Attribute name cannot be null ");
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		
		this.name = name;
		this.value = value;
	}

	public String getName(){
		return name;
	}
	
	public Object getValue(){
		return value;
	}
}

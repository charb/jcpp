package com.example;

/*
 * Hello.java - MBean implementation for the Hello MBean. This class must
 * implement all the Java methods declared in the HelloMBean interface,
 * with the appropriate behavior for each one.
 */


public class Hello implements HelloMBean {

	public void sayHello() {
		System.out.println("hello, world");
	}

	public int add(int x, int y) {
		return x + y;
	}


	public String getName() {
		return this.name;
	}

	/*
	 * Getter for the CacheSize attribute. The pattern shown here is frequent:
	 * the getter returns a private field representing the attribute value, and
	 * the setter changes that field.
	 */
	public int getCacheSize() {
		return this.cacheSize;
	}

	/*
	 * Setter for the CacheSize attribute. To avoid problems with stale values
	 * in multithreaded situations, it is a good idea for setters to be
	 * synchronized.
	 */
	public synchronized void setCacheSize(int size) {
		int oldSize = this.cacheSize;
		this.cacheSize = size;

		System.out.println("Cache size now " + this.cacheSize);
	}

	private final String name = "Reginald";
	private int cacheSize = DEFAULT_CACHE_SIZE;
	private static final int DEFAULT_CACHE_SIZE = 200;

}


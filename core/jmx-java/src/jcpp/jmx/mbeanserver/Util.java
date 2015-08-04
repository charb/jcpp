package jcpp.jmx.mbeanserver;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.HashSet;
import java.util.IdentityHashMap;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.SortedMap;
import java.util.TreeMap;

public class Util {

	static <K, V> Map<K, V> newInsertionOrderMap() {
		return new LinkedHashMap<K, V>();
	}

	static <K, V> Map<K, V> newMap() {
		return new HashMap<K, V>();
	}

	static <E> List<E> newList() {
		return new ArrayList<E>();
	}
	
	static <E> List<E> newList(Collection<E> c){
		return new ArrayList<E> (c);
	}
	
	static <E> Set<E> newSet(){
		return new HashSet<E>();
	}
	
	
	@SuppressWarnings("unchecked")
	public static <T> T cast(Object x){
		return (T) x;
	}
	
	static <K, V> IdentityHashMap<K, V> newIdentityHashMap(){
		return new IdentityHashMap<K, V>();
	}
	

}

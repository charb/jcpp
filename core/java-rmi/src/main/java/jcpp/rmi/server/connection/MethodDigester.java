package jcpp.rmi.server.connection;

import java.lang.reflect.Method;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

import java.util.HashMap;
import java.util.Map;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;


public class MethodDigester {
    private static Log log = LogFactory.getLog(MethodDigester.class);
    private Map<Class<?>, Map<Long, Method>> digestToMethodMap;
    private Map<Class<?>, Map<Method, Long>> methodToDigestMap;


    public MethodDigester() {
        this.digestToMethodMap = new HashMap<Class<?>, Map<Long, Method>>();
        this.methodToDigestMap = new HashMap<Class<?>, Map<Method, Long>>();
    }


    public synchronized Method getMethodFromDigest(Object object, long digest) {
        Class<?> classObject = object.getClass();
        Map<Long, Method> internalMap = digestToMethodMap.get(classObject);
        if (internalMap == null) {
            createDigests(classObject);
            internalMap = digestToMethodMap.get(classObject);
        }
        return internalMap.get(digest);
    }

    public synchronized Method[] getMethods(Object object) {
        Class<?> classObject = object.getClass();
        Map<Long, Method> internalMap = digestToMethodMap.get(classObject);
        if (internalMap == null) {
            createDigests(classObject);
            internalMap = digestToMethodMap.get(classObject);
        }
        return internalMap.values().toArray(new Method[0]);
    }

    public synchronized long getDigestFromMethod(Method method) {
        Class<?> classObject = method.getDeclaringClass();
        Map<Method, Long> internalMap = methodToDigestMap.get(classObject);
        if (internalMap == null) {
            createDigests(classObject);
            internalMap = methodToDigestMap.get(classObject);
        }
        return internalMap.get(method);
    }

    public synchronized void clear() {
        this.digestToMethodMap.clear();
        this.methodToDigestMap.clear();
    }

    static Object[] array = new Object[0];

    private void createDigests(Class<?> classObject) {
        Map<Long, Method> iDigestToMethodMap = new HashMap<Long, Method>();
        Map<Method, Long> iMethodToDigestMap = new HashMap<Method, Long>();

        Method[] methods = classObject.getMethods();
        for (Method method : methods) {
            method.setAccessible(true);
            Class<?>[] paramTypes = method.getParameterTypes();
            String args = "";
            for (Class<?> paramType : paramTypes) {
                if (paramType.isArray() && !paramType.getComponentType().isPrimitive()){
                    args += array.getClass().getName() + ",";//TODO till we are able to detect array of X in C++ code
                }else{
                    args += paramType.getName() + ",";
                }
            }
            String methodId = method.getName() + ":" + (args.length()>0 ? args.substring(0, args.length()-1) : "");
            Long digestLong = new Long(methodId.hashCode());
            iDigestToMethodMap.put(digestLong, method);
            iMethodToDigestMap.put(method, digestLong);
        }
        digestToMethodMap.put(classObject, iDigestToMethodMap);
        methodToDigestMap.put(classObject, iMethodToDigestMap);
    }

}

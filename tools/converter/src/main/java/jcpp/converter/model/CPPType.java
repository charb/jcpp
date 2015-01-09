package jcpp.converter.model;

import java.util.*;

public class CPPType implements Comparable{
    public enum Type{
        ARRAY(false), OBJECT(false),
        BOOLEAN(true), BYTE(true), 
        CHAR(true), DOUBLE(true), 
        FLOAT(true), INT(true), 
        LONG(true), SHORT(true), 
        VOID(true);
        protected boolean primitive;

        Type(boolean b){
            primitive=b;
        }

        public boolean isPrimitive(){
            return primitive;
        }
    };
    protected Type type;
    protected List<String> namespaces;
    protected String name;
    protected CPPType elementType;
    protected int dimensions;

	public CPPType(){
        this.namespaces=new ArrayList<String>();
	}

    public CPPType(Type type,String name,List<String> namespaces){
        this.type=type;
        this.name=name;
        this.namespaces=namespaces;
    }

    public CPPType(Type type,String name,List<String> namespaces,CPPType elementType){
        this.type=type;
        this.name=name;
        this.namespaces=namespaces;
        this.elementType=elementType;
    }

    public CPPType(String name,List<String> namespaces){
        type=Type.OBJECT;
        this.name=name;
        this.namespaces=namespaces;
    }

    public CPPType(CPPType t,String name){
        this.type=t.type;
        this.namespaces=new ArrayList<String>();
        namespaces.addAll(t.namespaces);
        this.name=name;
        elementType=t.elementType;
        dimensions=t.dimensions;
    }

    public static CPPType BOOLEAN_TYPE = new CPPType(Type.BOOLEAN,"jbool",new ArrayList<String>());

    public static CPPType BYTE_TYPE = new CPPType(Type.BYTE,"jbyte",new ArrayList<String>());

    public static CPPType CHAR_TYPE = new CPPType(Type.CHAR,"jchar",new ArrayList<String>());

    public static CPPType DOUBLE_TYPE = new CPPType(Type.DOUBLE,"jdouble",new ArrayList<String>());

    public static CPPType FLOAT_TYPE = new CPPType(Type.FLOAT,"jfloat",new ArrayList<String>());

    public static CPPType INT_TYPE = new CPPType(Type.INT,"jint",new ArrayList<String>());

    public static CPPType LONG_TYPE = new CPPType(Type.LONG,"jlong",new ArrayList<String>());

    public static CPPType SHORT_TYPE = new CPPType(Type.SHORT,"jshort",new ArrayList<String>());

    public static CPPType VOID_TYPE = new CPPType(Type.VOID,"void",new ArrayList<String>());

    public static CPPType BOOLEAN_ARRAY_TYPE = new CPPType(Type.ARRAY,"JPrimitiveBooleanArray",Arrays.asList("jcpp","lang"),BOOLEAN_TYPE);

    public static CPPType BYTE_ARRAY_TYPE = new CPPType(Type.ARRAY,"JPrimitiveByteArray",Arrays.asList("jcpp","lang"),BYTE_TYPE);

    public static CPPType CHAR_ARRAY_TYPE = new CPPType(Type.ARRAY,"JPrimitiveCharArray",Arrays.asList("jcpp","lang"),CHAR_TYPE);

    public static CPPType DOUBLE_ARRAY_TYPE = new CPPType(Type.ARRAY,"JPrimitiveDoubleArray",Arrays.asList("jcpp","lang"),DOUBLE_TYPE);

    public static CPPType FLOAT_ARRAY_TYPE = new CPPType(Type.ARRAY,"JPrimitiveFloatArray",Arrays.asList("jcpp","lang"),FLOAT_TYPE);

    public static CPPType INT_ARRAY_TYPE = new CPPType(Type.ARRAY,"JPrimitiveIntArray",Arrays.asList("jcpp","lang"),INT_TYPE);

    public static CPPType LONG_ARRAY_TYPE = new CPPType(Type.ARRAY,"JPrimitiveLongArray",Arrays.asList("jcpp","lang"),LONG_TYPE);

    public static CPPType SHORT_ARRAY_TYPE = new CPPType(Type.ARRAY,"JPrimitiveShortArray",Arrays.asList("jcpp","lang"),SHORT_TYPE);

    public static CPPType getArrayType(CPPType elementType){
        return new CPPType(Type.ARRAY,"JPrimitiveObjectArray", Arrays.asList("jcpp","lang"), elementType);
    }

    public boolean isPrimitive(){
        return getType().isPrimitive();
    }

    public String getName(){
        return name;
    }

    public void setName(String n){
        name=n;
    }

    public Type getType(){
        return type;
    }

    public void setType(Type t){
        type=t;
    }

    public List<String> getNamespaces(){
        return namespaces;
    }

    public void setNamespaces(List<String> ns){
        namespaces=ns;
    }

    public void addNamespace(String n){
        namespaces.add(n);
    }

    public CPPType getElementType(){
        return elementType;
    }

    public void setElementType(CPPType elementType){
        this.elementType=elementType;
    }

    public int getDimensions(){
        return dimensions;
    }

    public void setDimensions(int c){
        dimensions=c;
    }

    public int hashCode(){
        return namespaces.hashCode()+name.hashCode();
    }

    public String getIncludePath(){
        String s="";
        for (String ns : namespaces){
            s+=ns+"/";
        }
        s+=name+".h";
        return s;
    }

    public String getUsingNamespace(){
        String s="";
        for (String ns : getNamespaces()){
            s+=ns+"::";
        }
        if (s.length()>0){
            s=s.substring(0,s.length()-2);
        }
        return s;
    }

    public boolean equals(Object o){
        CPPType other=(CPPType)o;
        return namespaces.equals(other.namespaces) &&
               name.equals(other.name);
    }

    public int compareTo(Object o){
        CPPType type=(CPPType)o;
        if (namespaces.size()<type.namespaces.size()){
            return -1;

        }else if (namespaces.size()>type.namespaces.size()){
            return 1;
        }
        for (int i=0;i<namespaces.size();i++){
            int nb=namespaces.get(i).compareTo(type.namespaces.get(i));
            if (nb!=0){
                return nb;
            }
        }
        return name.compareTo(type.name);
    }

    public String toString(){
        return "[Type:"+type+",Namespaces:"+namespaces+",Name:"+name+"]";
    }
}
package jcpp;

import java.io.*;

public class SampleObject implements Serializable{
	private int i;
	private long l;
	private short s;
	private float f;
	private double d;
	private boolean bo;
	private char c;
	private byte by;

    public SampleObject(int i,long l,short s,float f,double d,boolean bo,char c,byte by){
        this.i=i;
        this.l=l;
        this.s=s;
        this.f=f;
        this.d=d;
        this.bo=bo;
        this.c=c;
        this.by=by;
    }

    public SampleObject(){
    }

    public int getInt(){
        return i;
    }

    public void setInt(int i){
        this.i=i;
    }

    public long getLong(){
        return l;
    }

    public void setLong(long l){
        this.l=l;
    }

    public short getShort(){
        return s;
    }

    public void setShort(short s){
        this.s=s;
    }

    public float getFloat(){
        return f;
    }

    public void setFloat(float f){
        this.f=f;
    }

    public double getDouble(){
        return d;
    }

    public void setDouble(double d){
        this.d=d;
    }

    public boolean getBoolean(){
        return bo;
    }

    public void setBoolean(boolean b){
        this.bo=b;
    }

    public char getChar(){
        return c;
    }

    public void setChar(char c){
        this.c=c;
    }

    public byte getByte(){
        return by;
    }

    public void setByte(byte b){
        this.by=b;
    }
}

package jcpp.rmi.server;

import java.io.*;

public class SampleObject implements Serializable{
	private static final long serialVersionUID = 40;
	public boolean bool1=true;
	public byte byte1=1;
	public char c1='c';
	public double d1=1;
	public float f1=2;
	public long l1=3;
	public short s1=4;
	public int i1=5;
	public IRemoteSample rs;

	SampleObject(){
	}

	public String toString(){
		return "[bool1:"+bool1+"]"+
				"[byte1:"+byte1+"]"+
				"[c1:"+c1+"]"+
				"[d1:"+d1+"]"+
				"[f1:"+f1+"]"+
				"[l1:"+l1+"]"+
				"[s1:"+s1+"]"+
				"[i1:"+i1+"]"+
				"[rs:"+rs+"]";
	}
}
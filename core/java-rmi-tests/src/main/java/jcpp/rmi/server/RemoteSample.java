package jcpp.rmi.server;

import java.io.*;

public class RemoteSample implements IRemoteSample{

	public RemoteSample(){
	}

	public SampleObject getSampleObject(){
		SampleObject so=new SampleObject();
		so.rs=this;
		return so;
	}

    public IRemoteSample getRemoteSample(){
    	return this;
    }

    public void checkRemoteSample(IRemoteSample rs) throws Exception{
    	if (rs!=this){
    		throw new Exception("bug when unmarshalling");
    	}
    }

	public void checkCallback(IRemoteSample rs) throws Exception{
		System.out.println("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!debut de checkCallback!!!!!!!!!!!!!!!!!!!!!!!!!");
		System.out.println("rs=="+rs);
    	System.out.println("rs.getSampleObject()=="+rs.getSampleObject());
    }
}
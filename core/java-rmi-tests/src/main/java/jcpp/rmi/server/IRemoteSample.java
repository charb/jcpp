package jcpp.rmi.server;

import java.io.*;

public interface IRemoteSample{

	public SampleObject getSampleObject();

    public IRemoteSample getRemoteSample();

    public void checkRemoteSample(IRemoteSample rs) throws Exception;

    public void checkCallback(IRemoteSample rs) throws Exception;
}
package outlook.client;

public interface IOutlookServer {
	
	void setTempFolder(String path);
	
	String getTempFolder();
	
	void openMailMessageInOutlook(MailMessage msg);
	
	void shutdown();
	
}

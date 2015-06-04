package outlook.client;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;


public class MailMessage implements Serializable {
	private static final long serialVersionUID = 5916566037215035809L;
	
	protected List<String> ccList;
	protected List<String> bccList;
	protected List<String> toList;
	
	protected String body;
	protected String subject;
	
	public MailMessage() {
		
	}
	
	
	public String getBody() {
		return body;
	}
	
	public void setBody(String body) {
		this.body = body;
	}
	
	public String getSubject() {
		return subject;
	}
	
	public void setSubject(String subject) {
		this.subject = subject;
	}
	
	public List<String> getCcList() {
		if(ccList == null) {
			ccList = new ArrayList<String>();
		}
		return ccList;
	}

	public void setCcList(List<String> ccList) {
		this.ccList = ccList;
	}

	public List<String> getBccList() {
		if(bccList == null) {
			bccList = new ArrayList<String>();
		}
		return bccList;
	}

	public void setBccList(List<String> bccList) {
		this.bccList = bccList;
	}

	public List<String> getToList() {
		if(toList == null) {
			toList = new ArrayList<String>();
		}
		return toList;
	}

	public void setToList(List<String> toList) {
		this.toList = toList;
	}
	
}

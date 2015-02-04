package jcpp.parser.cpp.update;

public class UpdatesResult {
    private final StringBuilder content;
	private final String originalContent;
	

    public UpdatesResult(String content) {
        originalContent = content;
		this.content = new StringBuilder(content);
    }


    public void replace(int start, int end, String str) {
        content.replace(start, end, str);
    }

    public void insert(int start, String str) {
        content.insert(start, str);
    }

    public char charAt(int index) {
        return content.charAt(index);
    }
    
    public String getSubstring(int start, int length) {
        return originalContent.substring(start, start + length);
    }

    public String getContent() {
        return content.toString();
    }

	public String getOriginalContent() {
		return originalContent;
	}
}

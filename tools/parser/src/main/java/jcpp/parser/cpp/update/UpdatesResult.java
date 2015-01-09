package jcpp.parser.cpp.update;

public class UpdatesResult {
    private StringBuilder content;


    public UpdatesResult(String content) {
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

    public String getContent() {
        return content.toString();
    }
}

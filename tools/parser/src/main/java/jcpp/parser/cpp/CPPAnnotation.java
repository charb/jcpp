package jcpp.parser.cpp;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

import org.eclipse.cdt.core.dom.ast.IASTComment;


@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class CPPAnnotation {
    private static final Pattern ANNOTATION_PATTERN = Pattern.compile("@(\\w+)\\s*\\((.*)\\)");
    private static final Pattern ANNOTATION_PROPERTY_PATTERN = Pattern.compile("(\\w+)\\s*=\\s*\"?(.*?)\"?\\s*(,|\\z)");

    @XmlAttribute
    private String name;
    private HashMap<String, String> properties;

    @XmlTransient
    private IASTComment astComment;


    public CPPAnnotation() {
        this.properties = new HashMap<String, String>(1);
    }

    public CPPAnnotation(IASTComment astComment) {
        this();
        this.astComment = astComment;
    }


    public static List<CPPAnnotation> parseAnnotations(IASTComment astComment) {
        String comment = new String(astComment.getComment());
        Matcher matcherAnnotation = ANNOTATION_PATTERN.matcher(comment);
        List<CPPAnnotation> cppAnnotations = new ArrayList<CPPAnnotation>(2);
        while (matcherAnnotation.find()) {
            CPPAnnotation cppAnnotation = new CPPAnnotation(astComment);
            cppAnnotation.name = matcherAnnotation.group(1);
            String props = matcherAnnotation.group(2);
            Matcher matcherProperty = ANNOTATION_PROPERTY_PATTERN.matcher(props);
            while (matcherProperty.find()) {
                cppAnnotation.properties.put(matcherProperty.group(1), matcherProperty.group(2));
            }
            cppAnnotations.add(cppAnnotation);
        }
        return cppAnnotations;
    }

    public String getName() {
        return name;
    }

    public HashMap<String, String> getProperties() {
        return properties;
    }

    public String getProperty(String key) {
        return properties.get(key);
    }

    public IASTComment getAstComment() {
        return astComment;
    }

    @Override
    public String toString() {
        return getClass().getSimpleName() + " [name: " + name + "][properties: " + properties + "]";
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = (prime * result) + ((name == null) ? 0 : name.hashCode());
        result = (prime * result) + ((properties == null) ? 0 : properties.hashCode());
        return result;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (obj == null) {
            return false;
        }
        if (!(obj instanceof CPPAnnotation)) {
            return false;
        }
        CPPAnnotation other = (CPPAnnotation) obj;
        if (name == null) {
            if (other.name != null) {
                return false;
            }
        } else if (!name.equals(other.name)) {
            return false;
        }
        if (properties == null) {
            if (other.properties != null) {
                return false;
            }
        } else if (!properties.equals(other.properties)) {
            return false;
        }
        return true;
    }

}

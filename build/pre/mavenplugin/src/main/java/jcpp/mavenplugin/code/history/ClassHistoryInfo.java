package jcpp.mavenplugin.code.history;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlRootElement;


@XmlRootElement
@XmlAccessorType(XmlAccessType.NONE)
public class ClassHistoryInfo {

    @XmlAttribute
    private String name;

    @XmlAttribute
    private String namespace;


    public ClassHistoryInfo() {

    }

    public ClassHistoryInfo(String name, String namespace) {
        this.name = name;
        this.namespace = namespace;
    }


    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getNamespace() {
        return namespace;
    }

    public void setNamespace(String namespace) {
        this.namespace = namespace;
    }

}

package jcpp.mavenplugin.code.history;

import java.util.ArrayList;
import java.util.List;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlElementRef;
import javax.xml.bind.annotation.XmlElementWrapper;
import javax.xml.bind.annotation.XmlRootElement;


@XmlRootElement
@XmlAccessorType(XmlAccessType.NONE)
public class TupleHistoryInfo {

    @XmlAttribute
    private String name;

    @XmlAttribute
    private String namespace;

    @XmlElementWrapper(name = "classHistoryInfos")
    @XmlElementRef
    private List<ClassHistoryInfo> classHistoryInfos;


    public TupleHistoryInfo() {
        classHistoryInfos = new ArrayList<ClassHistoryInfo>();
    }

    public TupleHistoryInfo(String name, String namespace) {
        this();
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

    public List<ClassHistoryInfo> getClassHistoryInfos() {
        return classHistoryInfos;
    }

    public void setClassHistoryInfos(List<ClassHistoryInfo> classHistoryInfos) {
        this.classHistoryInfos = classHistoryInfos;
    }

    public void addClassHistoryInfo(ClassHistoryInfo classHistoryInfo) {
        classHistoryInfos.add(classHistoryInfo);
    }

}

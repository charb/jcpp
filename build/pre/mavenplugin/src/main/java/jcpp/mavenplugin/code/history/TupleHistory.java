package jcpp.mavenplugin.code.history;

import java.io.File;
import java.io.IOException;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlElementRef;
import javax.xml.bind.annotation.XmlElementWrapper;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

import jcpp.mavenplugin.code.CppFileTuple;

import org.apache.commons.io.FileUtils;


@XmlRootElement
@XmlAccessorType(XmlAccessType.NONE)
public class TupleHistory implements Comparable<TupleHistory> {

    @XmlAttribute
    private String name;

    @XmlAttribute
    private String namespace;

    @XmlElement
    private FileHistory headerFileHistory;

    @XmlElement
    private FileHistory cppFileHistory;

    @XmlElementWrapper(name = "generatedTuplesHistory")
    @XmlElementRef
    private List<TupleHistory> generatedTuplesHistory;

    @XmlElement
    private TupleHistoryInfo tupleHistoryInfo;

    @XmlTransient
    private CppFileTuple cppFileTuple;


    public TupleHistory() {
    }

    public TupleHistory(String name, String namespace, FileHistory headerFileHistory, FileHistory cppFileHistory) {
        this.name = name;
        this.namespace = namespace;
        this.headerFileHistory = headerFileHistory;
        this.cppFileHistory = cppFileHistory;
    }


    public TupleHistory findGeneratedTupleHistory(String name) {
        int searchIndex = (generatedTuplesHistory == null) ? -1 : Collections.binarySearch(generatedTuplesHistory, new TupleHistory(name, null, null, null));
        return (searchIndex < 0) ? null : generatedTuplesHistory.get(searchIndex);
    }

    public void sort() {
        if (generatedTuplesHistory != null) {
            Collections.sort(generatedTuplesHistory);
            for (TupleHistory generatedTupleHistory : generatedTuplesHistory) {
                generatedTupleHistory.sort();
            }
        }
    }

    public void delete(File historyHeaderBaseDir, File historyCppBaseDir) {
        if (headerFileHistory != null) {
            File headerFile = new File(historyHeaderBaseDir, headerFileHistory.getPath());
            FileUtils.deleteQuietly(headerFile);
        }

        if (cppFileHistory != null) {
            File cppFile = new File(historyCppBaseDir, cppFileHistory.getPath());
            FileUtils.deleteQuietly(cppFile);
        }

        if (generatedTuplesHistory != null) {
            for (TupleHistory generatedTupleHistory : generatedTuplesHistory) {
                generatedTupleHistory.delete(historyHeaderBaseDir, historyCppBaseDir);
            }
        }
    }

    public void copy(File historyHeaderBaseDir, File historyCppBaseDir, File dstHeaderBaseDir, File dstCppBaseDir, boolean updateIncludeDirOnly) throws IOException {
        if (headerFileHistory != null) {
            File originalHeaderFile = new File(historyHeaderBaseDir, headerFileHistory.getPath());
            File copyHeaderFile = new File(dstHeaderBaseDir, headerFileHistory.getPath());
            FileUtils.copyFile(originalHeaderFile, copyHeaderFile);
        }

        if (!updateIncludeDirOnly) {
            if (cppFileHistory != null) {
                File originalCppFile = new File(historyCppBaseDir, cppFileHistory.getPath());
                File copyCppFile = new File(dstCppBaseDir, cppFileHistory.getPath());
                FileUtils.copyFile(originalCppFile, copyCppFile);
            }
        }

        if ((generatedTuplesHistory != null) && (generatedTuplesHistory.size() > 0)) {
            for (TupleHistory generatedTupleHistory : generatedTuplesHistory) {
                generatedTupleHistory.copy(historyHeaderBaseDir, historyCppBaseDir, dstHeaderBaseDir, dstCppBaseDir, false);
            }
        }
    }

    public CppFileTuple getCppFileTuple() {
        return cppFileTuple;
    }

    public void setCppFileTuple(CppFileTuple cppFileTuple) {
        this.cppFileTuple = cppFileTuple;
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

    public FileHistory getHeaderFileHistory() {
        return headerFileHistory;
    }

    public void setHeaderFileHistory(FileHistory headerFileHistory) {
        this.headerFileHistory = headerFileHistory;
    }

    public FileHistory getCppFileHistory() {
        return cppFileHistory;
    }

    public void setCppFileHistory(FileHistory cppFileHistory) {
        this.cppFileHistory = cppFileHistory;
    }

    public TupleHistoryInfo getTupleHistoryInfo() {
        return tupleHistoryInfo;
    }

    public void setTupleHistoryInfo(TupleHistoryInfo tupleHistoryInfo) {
        this.tupleHistoryInfo = tupleHistoryInfo;
    }

    public List<TupleHistory> getGeneratedTuplesHistory() {
        return generatedTuplesHistory;
    }

    public void setGeneratedTuplesHistory(List<TupleHistory> generatedTuplesHistory) {
        this.generatedTuplesHistory = generatedTuplesHistory;
    }

    public void addGeneratedTuplsHistory(TupleHistory generatedTupleHistory) {
        if (generatedTuplesHistory == null) {
            generatedTuplesHistory = new ArrayList<TupleHistory>();
        }
        generatedTuplesHistory.add(generatedTupleHistory);
    }

    @Override
    public String toString() {
        return (new StringBuilder()).append("Tuple History (H:").append((headerFileHistory == null) ? "N" : "Y").append(",CPP:").append((cppFileHistory == null) ? "N" : "Y").append(",G:").append(
            (generatedTuplesHistory == null) ? "0" : String.valueOf(generatedTuplesHistory.size())).append(")").append(" namespace: ").append(namespace).append(" name: ").append(name).toString();
    }

    @Override
    public int compareTo(TupleHistory o) {
        return name.compareTo(o.name);
    }

}

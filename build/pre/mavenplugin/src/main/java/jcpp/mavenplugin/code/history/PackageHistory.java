package jcpp.mavenplugin.code.history;

import java.io.File;
import java.io.IOException;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlElementRef;
import javax.xml.bind.annotation.XmlElementWrapper;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

import jcpp.mavenplugin.code.CppPackage;


@XmlRootElement
@XmlAccessorType(XmlAccessType.NONE)
public class PackageHistory implements Comparable<PackageHistory> {

    @XmlAttribute
    private String name;

    @XmlAttribute
    private String namespace;

    @XmlElementWrapper(name = "tuplesHistory")
    @XmlElementRef
    private List<TupleHistory> tuplesHistory;

    @XmlElementWrapper(name = "generatedTuplesHistory")
    @XmlElementRef
    private List<TupleHistory> generatedTuplesHistory;

    @XmlElementWrapper(name = "subPackagesHistory")
    @XmlElementRef
    private List<PackageHistory> subPackagesHistory;

    @XmlTransient
    private CppPackage cppPackage;


    public PackageHistory() {
    }

    public PackageHistory(String name, String namespace) {
        this.name = name;
        this.namespace = namespace;
    }


    public PackageHistory findPackageHistory(String[] namespace, int index) {
        int searchIndex = (subPackagesHistory == null) ? -1 : Collections.binarySearch(subPackagesHistory, new PackageHistory(namespace[index], null));
        return (searchIndex < 0) ? null : ((index == (namespace.length - 1)) ? subPackagesHistory.get(searchIndex) : subPackagesHistory.get(searchIndex).findPackageHistory(namespace, index + 1));
    }

    public TupleHistory findTupleHistory(String name) {
        int searchIndex = (tuplesHistory == null) ? -1 : Collections.binarySearch(tuplesHistory, new TupleHistory(name, null, null, null));
        return (searchIndex < 0) ? null : tuplesHistory.get(searchIndex);
    }

    public TupleHistory findGeneratedTupleHistory(String name) {
        int searchIndex = (generatedTuplesHistory == null) ? -1 : Collections.binarySearch(generatedTuplesHistory, new TupleHistory(name, null, null, null));
        if (searchIndex >= 0) {
            return generatedTuplesHistory.get(searchIndex);
        } else if (tuplesHistory != null) {
            for (TupleHistory tupleHistory : tuplesHistory) {
                TupleHistory generatedTupleHistory = tupleHistory.findGeneratedTupleHistory(name);
                if (generatedTupleHistory != null) {
                    return generatedTupleHistory;
                }
            }
        }
        return null;
    }

    public void sort() {
        if (tuplesHistory != null) {
            Collections.sort(tuplesHistory);
            for (TupleHistory tupleHistory : tuplesHistory) {
                tupleHistory.sort();
            }
        }
        if (generatedTuplesHistory != null) {
            Collections.sort(generatedTuplesHistory);
            for (TupleHistory generatedTupleHistory : generatedTuplesHistory) {
                generatedTupleHistory.sort();
            }
        }
        if (subPackagesHistory != null) {
            Collections.sort(subPackagesHistory);
            for (PackageHistory subPackageHistory : subPackagesHistory) {
                subPackageHistory.sort();
            }
        }
    }

    public void deletePackageGeneratedTuples(File headerBaseDir, File cppBaseDir) {
        if (generatedTuplesHistory != null) {
            for (TupleHistory generatedTupleHistory : generatedTuplesHistory) {
                generatedTupleHistory.delete(headerBaseDir, cppBaseDir);
            }
        }
    }

    public void deleteLeftOverHistory(File headerBaseDir, File cppBaseDir) {
        if (tuplesHistory != null) {
            for (TupleHistory tupleHistory : tuplesHistory) {
                if (tupleHistory.getCppFileTuple() == null) {
                    tupleHistory.delete(headerBaseDir, cppBaseDir);
                }
            }
        }
        if (cppPackage == null) {
            deletePackageGeneratedTuples(headerBaseDir, cppBaseDir);
        }
        if (subPackagesHistory != null) {
            for (PackageHistory subPackageHistory : subPackagesHistory) {
                subPackageHistory.deleteLeftOverHistory(headerBaseDir, cppBaseDir);
            }
        }

    }

    public CppPackage getCppPackage() {
        return cppPackage;
    }

    public void setCppPackage(CppPackage cppPackage) {
        this.cppPackage = cppPackage;
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

    public List<TupleHistory> getTuplesHistory() {
        return tuplesHistory;
    }

    public void setTuplesHistory(List<TupleHistory> tuplesHistory) {
        this.tuplesHistory = tuplesHistory;
    }

    public void addTupleHistory(TupleHistory tupleHistory) {
        if (tuplesHistory == null) {
            tuplesHistory = new ArrayList<TupleHistory>();
        }
        tuplesHistory.add(tupleHistory);
    }

    public List<TupleHistory> getGeneratedTuplesHistory() {
        return generatedTuplesHistory;
    }

    public void setGeneratedTuplesHistory(List<TupleHistory> generatedTuplesHistory) {
        this.generatedTuplesHistory = generatedTuplesHistory;
    }

    public void addGeneratedTupleHistory(TupleHistory generatedTupleHistory) {
        if (generatedTuplesHistory == null) {
            generatedTuplesHistory = new ArrayList<TupleHistory>();
        }
        generatedTuplesHistory.add(generatedTupleHistory);
    }

    public List<PackageHistory> getSubPackagesHistory() {
        return subPackagesHistory;
    }

    public void setSubPackagesHistory(List<PackageHistory> subPackagesHistory) {
        this.subPackagesHistory = subPackagesHistory;
    }

    public void addSubPackageHistory(PackageHistory subPackageHistory) {
        if (subPackagesHistory == null) {
            subPackagesHistory = new ArrayList<PackageHistory>();
        }
        subPackagesHistory.add(subPackageHistory);
    }

    public PackageHistory createNewHistoryFromExisting() {
        PackageHistory packageHistory = new PackageHistory(name, namespace);
        packageHistory.setGeneratedTuplesHistory(generatedTuplesHistory);
        return packageHistory;
    }

    public void copyGeneratedTuples(File historyHeaderBaseDir, File historyCppBaseDir, File dstHeaderBaseDir, File dstCppBaseDir, boolean updateIncludeDirOnly) throws IOException {
        if (generatedTuplesHistory != null) {
            for (TupleHistory generatedTupleHistory : generatedTuplesHistory) {
                generatedTupleHistory.copy(historyHeaderBaseDir, historyCppBaseDir, dstHeaderBaseDir, dstCppBaseDir, updateIncludeDirOnly);
            }
        }
    }

    @Override
    public String toString() {
        return "PackageHistory [namespace=" + namespace + "]";
    }

    @Override
    public int compareTo(PackageHistory o) {
        return name.compareTo(o.name);
    }

}

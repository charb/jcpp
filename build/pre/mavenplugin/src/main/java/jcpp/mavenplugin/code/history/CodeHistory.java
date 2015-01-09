package jcpp.mavenplugin.code.history;

import java.io.File;

import javax.xml.bind.JAXBContext;
import javax.xml.bind.JAXBException;
import javax.xml.bind.Marshaller;
import javax.xml.bind.Unmarshaller;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;


@XmlRootElement
@XmlAccessorType(XmlAccessType.NONE)
public class CodeHistory {

    private static JAXBContext jaxbContext;

    @XmlElement
    private PackageHistory packageHistory;


    public CodeHistory() {
    }

    public CodeHistory(PackageHistory packageHistory) {
        this.packageHistory = packageHistory;
    }


    public static synchronized JAXBContext getJAXBContext() {
        if (jaxbContext == null) {
            try {
                jaxbContext = JAXBContext.newInstance(CodeHistory.class);
            } catch (JAXBException e) {
                throw new RuntimeException(e);
            }
        }
        return jaxbContext;
    }

    public static CodeHistory readFromFile(File file) throws Exception {
        Unmarshaller unmarshaller = getJAXBContext().createUnmarshaller();
        return (CodeHistory) unmarshaller.unmarshal(file);
    }

    public void writeToFile(File file) throws Exception {
        Marshaller marshaller = getJAXBContext().createMarshaller();
        marshaller.setProperty(Marshaller.JAXB_FORMATTED_OUTPUT, Boolean.TRUE);
        File parentFile = file.getParentFile();
        if (parentFile != null) {
            parentFile.mkdirs();
        }
        marshaller.marshal(this, file);
    }

    public void sort() {
        if (packageHistory != null) {
            packageHistory.sort();
        }
    }

    public PackageHistory getPackageHistory() {
        return packageHistory;
    }

    public void setPackageHistory(PackageHistory packageHistory) {
        this.packageHistory = packageHistory;
    }

    public PackageHistory findPackageHistory(String namespace) {
        if (packageHistory != null) {
            if (packageHistory.getNamespace().equals(namespace)) {
                return packageHistory;
            }
            return packageHistory.findPackageHistory(namespace.split("::"), 0);
        }
        return null;
    }

    public TupleHistory findTupleHistory(String namespace, String name) {
        PackageHistory namespacePackageHistory = findPackageHistory(namespace);
        return (namespacePackageHistory == null) ? null : namespacePackageHistory.findTupleHistory(name);
    }

    public TupleHistory findGeneratedTupleHistory(String namespace, String name) {
        PackageHistory namespacePackageHistory = findPackageHistory(namespace);
        return (namespacePackageHistory == null) ? null : namespacePackageHistory.findGeneratedTupleHistory(name);
    }

    public void deleteLeftOverHistory(File headerBaseDir, File cppBaseDir) {
        if (packageHistory != null) {
            packageHistory.deleteLeftOverHistory(headerBaseDir, cppBaseDir);
        }
    }
}

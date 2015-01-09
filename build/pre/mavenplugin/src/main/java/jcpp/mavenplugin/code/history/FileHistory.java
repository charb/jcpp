package jcpp.mavenplugin.code.history;

import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;

import java.util.zip.CRC32;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlRootElement;


@XmlRootElement
@XmlAccessorType(XmlAccessType.NONE)
public class FileHistory {

    @XmlAttribute
    private String path;

    @XmlAttribute
    private String crc;


    public FileHistory() {
    }

    public FileHistory(String path, File file) throws IOException {
        this.path = path;
        if (file != null) {
            crc = calculateFileCheckSum(file);
        }
    }


    public static String calculateFileCheckSum(File file) throws IOException {
        CRC32 crc = new CRC32();
        InputStream inputStream = new BufferedInputStream(new FileInputStream(file));
        try {
            int cnt;
            while ((cnt = inputStream.read()) != -1) {
                crc.update(cnt);
            }
        } finally {
            inputStream.close();
        }
        return Long.toHexString(crc.getValue());
    }

    public String getPath() {
        return path;
    }

    public void setPath(String path) {
        this.path = path;
    }

    public String getCrc() {
        return crc;
    }

    public void setCrc(String crc) {
        this.crc = crc;
    }

    @Override
    public String toString() {
        return "FileHistory [path=" + path + ", crc=" + crc + "]";
    }

}

package jcpp.rmi.server.compression;

import java.io.FilterOutputStream;
import java.io.IOException;
import java.io.OutputStream;

import java.util.concurrent.atomic.AtomicLong;
import java.util.zip.Deflater;

import jcpp.rmi.server.statistic.IStatisticStream;


public class CompressionOutputStream extends FilterOutputStream implements IStatisticStream {
    private int compressionThreshold;
    private byte[] compressedData;
    private byte[] uncompressedData;
    private int compressionType;
    private int uncompressedDataLength;
    private AtomicLong networkDataCounter;


    public CompressionOutputStream(OutputStream outputStream, int uncompressedBufferSize, int compressedBufferSize, int compressionThreshold, int compressionType) {
        super(outputStream);
        this.compressionType = compressionType;
        this.compressionThreshold = compressionThreshold;
        this.uncompressedData = new byte[uncompressedBufferSize];
        this.compressedData = new byte[compressedBufferSize];
        this.networkDataCounter = new AtomicLong();
    }


    @Override
    public void write(int b) throws IOException {
        uncompressedData[uncompressedDataLength++] = (byte) b;
        if (uncompressedDataLength >= uncompressedData.length) {
            sendCompressedData();
        }
    }

    @Override
    public void write(byte[] b, int off, int len) throws IOException {
        while ((uncompressedDataLength + len) > uncompressedData.length) {
            int toCopy = uncompressedData.length - uncompressedDataLength;
            System.arraycopy(b, off, uncompressedData, uncompressedDataLength, toCopy);
            uncompressedDataLength += toCopy;
            sendCompressedData();
            off += toCopy;
            len -= toCopy;
        }
        System.arraycopy(b, off, uncompressedData, uncompressedDataLength, len);
        uncompressedDataLength += len;
        sendCompressedData();

    }

    public void sendCompressedData() throws IOException {
        if (uncompressedDataLength > 0) {
            if (uncompressedDataLength >= compressionThreshold) {
                Deflater compressor = new Deflater(compressionType);
                try {
                    compressor.setInput(uncompressedData, 0, uncompressedDataLength);
                    compressor.finish();
                    int compressedDataLength = compressor.deflate(compressedData);
                    writeToStream(compressedData, compressedDataLength, true);
                } finally {
                    compressor.end();
                }
            } else {
                writeToStream(uncompressedData, uncompressedDataLength, false);
            }
            uncompressedDataLength = 0;
        }
    }

    public void writeToStream(byte[] data, int dataLength, boolean compressed) throws IOException {
        try {
            byte compressionByte = compressed ? (byte) 1 : (byte) 0;
            out.write(compressionByte);
            networkDataCounter.incrementAndGet();

            /*
             * if !compressed, dataLength == uncompressedDataLength
             */
            out.write(dataLength >> 24);
            out.write(dataLength >> 16);
            out.write(dataLength >> 8);
            out.write(dataLength);
            networkDataCounter.addAndGet(4);

            if (compressed) {
                out.write(uncompressedDataLength >> 24);
                out.write(uncompressedDataLength >> 16);
                out.write(uncompressedDataLength >> 8);
                out.write(uncompressedDataLength);
                networkDataCounter.addAndGet(4);
            }
            out.write(data, 0, dataLength);
            networkDataCounter.addAndGet(dataLength);

        } catch (Throwable throwable) {
            throw new IOException(throwable);
        }
    }

    @Override
    public void flush() throws IOException {
        sendCompressedData();
        out.flush();
    }

    @Override
    public void close() throws IOException {
        super.close();
    }

    @Override
    public AtomicLong getNetworkDataCounter() {
        return networkDataCounter;
    }

    @Override
    public void setNetworkDataCounter(AtomicLong networkDataCounter) {
        this.networkDataCounter = networkDataCounter;
    }

    @Override
    public boolean usesCompressionStream() {
        return true;
    }
}

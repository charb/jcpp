package jcpp.rmi.server.compression;

import java.io.EOFException;
import java.io.FilterInputStream;
import java.io.IOException;
import java.io.InputStream;

import java.util.concurrent.atomic.AtomicLong;
import java.util.zip.DataFormatException;
import java.util.zip.Inflater;

import jcpp.rmi.server.statistic.IStatisticStream;


public class CompressionInputStream extends FilterInputStream implements IStatisticStream {
    private byte[] inputData;
    private byte[] decompressedData;
    private int decompressedDataLength;
    private int readDataCounter;
    private boolean bCompressed;
    private AtomicLong networkDataCounter;


    public CompressionInputStream(InputStream in, int bufferSize) throws IOException {
        super(in);
        inputData = new byte[bufferSize];
        decompressedData = new byte[bufferSize];
        networkDataCounter = new AtomicLong();
    }


    @Override
    public int read() throws IOException {
        if (readDataCounter >= decompressedDataLength) {
            try {
                decompress();
            } catch (EOFException e) {
                return -1;
            }
        }
        return decompressedData[readDataCounter++] & 0xff;
    }

    @Override
    public int read(byte[] b, int off, int len) throws IOException {
        int count = 0;
        while (count < len) {
            if (readDataCounter >= decompressedDataLength) {
                try {
                    if ((count > 0) && (in.available() == 0)) {
                        return count;
                    } else {
                        decompress();
                    }
                } catch (EOFException eof) {
                    if (count == 0) {
                        count = -1;
                    }
                    return count;
                }
            }
            int toCopy = Math.min(decompressedDataLength - readDataCounter, len - count);
            System.arraycopy(decompressedData, readDataCounter, b, off + count, toCopy);
            readDataCounter += toCopy;
            count += toCopy;
        }
        assert (count == len);
        return count;
    }

    public void decompress() throws IOException {
        int compression = in.read();
        if (compression == -1) {
            throw new EOFException();
        }
        networkDataCounter.incrementAndGet();
        int[] len = new int[4];
        for (int i = 0; i < 4; i++) {
            len[i] = in.read();
            networkDataCounter.incrementAndGet();
            if (len[i] == -1) {
                throw new EOFException();
            }
        }
        bCompressed = (compression == 0) ? false : true;
        if (!bCompressed) {
            decompressedDataLength = (len[0] << 24) ^ (len[1] << 16) ^ (len[2] << 8) ^ len[3];
            networkDataCounter.addAndGet(decompressedDataLength);

            if (decompressedDataLength > decompressedData.length) {
                decompressedData = new byte[decompressedDataLength];
            }

            int lengthSum = 0;
            while (lengthSum < decompressedDataLength) {
                int length = in.read(decompressedData, lengthSum, decompressedDataLength - lengthSum);
                if (length == -1) {
                    throw new EOFException();
                }
                lengthSum += length;
            }
            assert (lengthSum == decompressedDataLength);

        } else {

            int inputDataLength = (len[0] << 24) ^ (len[1] << 16) ^ (len[2] << 8) ^ len[3];
            networkDataCounter.addAndGet(inputDataLength);

            for (int i = 0; i < 4; i++) {
                len[i] = in.read();
                if (len[i] == -1) {
                    throw new EOFException();
                }
                networkDataCounter.incrementAndGet();
            }

            if (inputDataLength > inputData.length) {
                inputData = new byte[inputDataLength];
            }

            decompressedDataLength = (len[0] << 24) ^ (len[1] << 16) ^ (len[2] << 8) ^ len[3];

            if (decompressedDataLength > decompressedData.length) {
                decompressedData = new byte[decompressedDataLength];
            }

            int lengthSum = 0;
            while (lengthSum < inputDataLength) {
                int length = in.read(inputData, lengthSum, inputDataLength - lengthSum);
                if (length == -1) {
                    throw new EOFException();
                }
                lengthSum += length;
            }
            assert (lengthSum == inputDataLength);

            Inflater decompressor = new Inflater();
            try {
                decompressor.setInput(inputData);
                decompressedDataLength = decompressor.inflate(decompressedData, 0, decompressedDataLength);
            } catch (DataFormatException dfe) {
                throw new IOException("Data format exception - " + dfe.getMessage());
            } finally {
                decompressor.end();
            }
        }
        readDataCounter = 0;
    }

    @Override
    public void close() throws IOException {
        super.close();
    }

    @Override
    public int available() throws IOException {
        return (decompressedDataLength - readDataCounter) + in.available();
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

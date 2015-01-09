package jcpp.rmi.server.transport;

import java.io.DataInputStream;
import java.io.EOFException;
import java.io.IOException;
import java.io.UTFDataFormatException;

import java.net.Socket;

import java.util.concurrent.Callable;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import jcpp.rmi.server.gateway.IGatewaySocket;


public class ConnectionHeaderReader implements Callable<Void> {
    private static Log log = LogFactory.getLog(ConnectionHeaderReader.class);
    private Socket socket;
    private Transport transport;


    public ConnectionHeaderReader(Socket socket, Transport transport) {
        this.socket = socket;
        this.transport = transport;
    }


    public void unexport() throws IOException {
        if (socket != null) {
            socket.close();
        }
    }

    @Override
    public Void call() throws Exception {
        String oldName = Thread.currentThread().getName();
        Thread.currentThread().setName("Connection Header Reader Thread - " + socket);
        Connection connection = null;
        try {
            DataInputStream in = new DataInputStream(socket.getInputStream());
            int magicNumber = in.readInt();
            if (magicNumber != TransportConfiguration.getMagicNumber()) {
                if (log.isDebugEnabled()) {
                    log.debug("Incorrect Magic Number (" + magicNumber + "). Socket - " + socket);
                }
                throw new EOFException();
            }
            EndPoint remoteEndPoint = new EndPoint(in);
            connection = new SocketConnection(socket, transport, transport.getTransportStatistic().createConnectionStatistic(remoteEndPoint), transport.getTransportConfiguration().getGatewayConfiguration());

            if (connection.isReusable()) {
                connection.sendOk();
            }

            do {
                byte msgType = in.readByte();
                if (msgType == TransportConfiguration.MSG_TYPE_PING) {
                    connection.sendOk();
                    if (!connection.isReusable()) {
                        connection.getOutputStream().flush();
                    }

                } else if (msgType == TransportConfiguration.MSG_TYPE_CALL) {
                    try {
                        transport.getTransportDispatcher().dispatch(remoteEndPoint, transport.getLocalEndPoint(), connection);
                    } catch (Throwable throwable) {
                        if (log.isDebugEnabled()) {
                            log.debug("Error in transport dispatcher while dispatching from: " + remoteEndPoint, throwable);
                        }
                        throw new Exception(throwable); // dispatch throws Throwable, but Void call() can only throw Exception
                    }

                    if (!connection.isReusable()) {
                        connection.sendOk(); // OK for magic number
                    }
                    connection.getOutputStream().flush();
                } else {
                    if (log.isDebugEnabled()) {
                        log.debug("Unknown message type. Socket: " + socket);
                    }
                    throw new EOFException();
                }

            } while (((IGatewaySocket) socket).isReausable() && !socket.isClosed());

        } catch (EOFException e1) {
            if (log.isDebugEnabled()) {
                log.debug("Error reading connection header. Socket: " + socket, e1);
            }
        } catch (UTFDataFormatException e2) {
            if (log.isDebugEnabled()) {
                log.debug("Error reading connection header. Socket: " + socket, e2);
            }
        } finally {
            try {
                if (connection != null) {
                    connection.kill();
                }
            } finally {
                transport.remove(this);
                Thread.currentThread().setName(oldName);
            }
        }
        return null;
    }

}

package com.project.barde.barde.static

import java.io.*
import java.net.Socket
import java.net.UnknownHostException
import java.nio.ByteBuffer

/**
 * Created by michael on 08/06/2018.
 */
class SocketServer(val listenerSocket: ListenerSocket) : Runnable {
    private lateinit var rec: PrintWriter
    private lateinit var get: BufferedReader
    private lateinit var client: Socket
    private lateinit var buffer: String
    private lateinit var reb: DataOutputStream
    var message: MutableList<Byte> = arrayListOf()
    var j = 0
    override fun run() {
        try {
            client = Socket("192.168.1.36", 23)
            //client = Socket("163.172.128.43", 23)
            //client = Socket("192.168.2.1", 23)

            if (client.isConnected) {
                println("connected")
                message.clear()
                get = BufferedReader(InputStreamReader(client.getInputStream()))
                rec = PrintWriter(client.getOutputStream(), true)
                reb = DataOutputStream(client.getOutputStream())
                while (true) {
                    var bytebuffer: ByteArray
                    bytebuffer = ByteArray(200)
                    var rn = 0;
                    rn = client.getInputStream().read(bytebuffer)
                    if (rn == -1) {
                        client.close()
                        return
                    }
                    for (i in 1..rn) {
                        if (rn > 1 && bytebuffer.get(i - 1).toChar() == '\n' && bytebuffer.get(i - 2).toChar() == '\r') {
                            var messageByte = ByteArray(message.size)
                            for (t in 1..message.size) {
                                messageByte.set(t - 1, message.get(t - 1))
                            }
                            listenerSocket.getListenerSocket(messageByte)
                            message.clear()
                        } else if (bytebuffer.get(i - 1).toChar() != '\n' && bytebuffer.get(i - 1).toChar() != '\r') {
                            message.add(bytebuffer.get(i - 1))
                            j++

                        }
                    }
                }
            } else {
                println("isNotConnexted")
            }


            // client.close()
        } catch (e: UnknownHostException) {
            e.printStackTrace()
        } catch (e: IOException) {
            e.printStackTrace()
        }
    }

    companion object {
        val MUSIQUEPARAM: Int = 0x1
        val STYLE: Int = 0x11
        val JAZZ: Int = 0x111
        val BLUES: Int = 0x211
        val CHORD: Int = 0x21
        val ARPEGE: Int = 0x31
        val DRUM: Int = 0x41
        val BPM: Int = 0x51

    }

    public fun rec(): PrintWriter {
        return rec
    }

    public fun client(): Socket {
        return client
    }
    public fun reb() : DataOutputStream {
        return reb
    }
    fun sendToServer(array: IntArray){
        var byteArray = ByteArray((array.size * 4))
        var index = 0
        for (i in 1..array.size){
            var byteBuffer = ByteBuffer.allocate(4).putInt(array[i - 1]).array()
            for (j in 1..byteBuffer.size){
                byteArray.set(index, byteBuffer.get(byteBuffer.size - j))
                index++
            }
        }
        reb.write(byteArray)
    }
}

interface ListenerSocket {
    fun getListenerSocket(buffer: ByteArray)
}
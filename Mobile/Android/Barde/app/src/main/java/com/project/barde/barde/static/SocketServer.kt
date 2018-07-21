package com.project.barde.barde.static

import android.widget.Toast
import org.jetbrains.anko.doAsync
import java.io.*
import java.net.Socket
import java.net.UnknownHostException
import java.nio.ByteBuffer

/**
 * Created by michael on 08/06/2018.
 */
class SocketServer(val listenerSocket: ListenerSocket, val ip: String) : Runnable {
    private lateinit var rec: PrintWriter
    private lateinit var get: BufferedReader
    private lateinit var client: Socket
    private lateinit var buffer: String
    private lateinit var reb: DataOutputStream
    var message: MutableList<Byte> = arrayListOf()
    var connectionIsSet = false
    var j = 0
    override fun run() {
        try {
            println("---------------------- ip = $ip")
            //client = Socket("129.12.131.98", 23)
            client = Socket(ip, 23)
            //client = Socket("192.168.2.1", 23)
            if (client.isConnected) {
                println("connected")
                message.clear()
                get = BufferedReader(InputStreamReader(client.getInputStream()))
                rec = PrintWriter(client.getOutputStream(), true)
                reb = DataOutputStream(client.getOutputStream())
                while (client.isConnected) {
                    var bytebuffer: ByteArray
                    bytebuffer = ByteArray(200)
                    var rn = 0;
                    rn = client.getInputStream().read(bytebuffer)
                    if (rn == -1) {
                        client.close()
                        return
                    }
                    for (i in 1..rn) {
                        if (rn >= 2 && bytebuffer.get(i - 1).toChar() == '\n' && bytebuffer.get(i - 2).toChar() == '\r') {
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
            listenerSocket.failedBindSocket(e.message)
            println("---------------------------------------1" + e.message)
        } catch (e: IOException) {
            listenerSocket.failedBindSocket(e.message)
            println("---------------------------------------2" + e.message)

        }
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
    fun close() {
        try{
            client.close()
        }catch (e : Exception){
            e.printStackTrace()
        }
    }
    fun sendToServer(array: IntArray) : Boolean{
        try{
            if (client.isConnected){
                var byteArray = ByteArray((array.size * 4))
                var index = 0
                for (i in 1..array.size){
                    var byteBuffer = ByteBuffer.allocate(4).putInt(array[i - 1]).array()
                    for (j in 1..byteBuffer.size){
                        byteArray.set(index, byteBuffer.get(byteBuffer.size - j))
                        index++
                    }
                }
                doAsync {
                    reb.write(byteArray)
                }

                return true
            }else{
                return false
            }
        }catch (e : Exception){
            println("message = " + e.message)

            return false
        }

    }
}

interface ListenerSocket {
    fun getListenerSocket(buffer: ByteArray)
    fun failedBindSocket(message : String?)
}
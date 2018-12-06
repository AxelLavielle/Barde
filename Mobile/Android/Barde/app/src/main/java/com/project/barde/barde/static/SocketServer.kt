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
class SocketServer(val listenerSocket: ListenerSocket, val ip: String, val port: Int) : Runnable {
    private lateinit var rec: PrintWriter
    private lateinit var get: BufferedReader
    private lateinit var client: Socket
    private lateinit var buffer: String
    private lateinit var reb: DataOutputStream
    var message: MutableList<Byte> = arrayListOf()
    var messageByte = ByteArray(0)
        var connectionIsSet = false
    var j = 0
    override fun run() {
        try {
            println("---------------------- ip = $ip")
            client  = Socket(ip, port)
            //client = Socket("129.12.131.98", 23)
            //client = Socket("163.172.128.43", 23)
            //client = Socket("192.168.2.1", 23)
            if (client.isConnected) {
                println("connected")
                message.clear()
                get = BufferedReader(InputStreamReader(client.getInputStream()))
                rec = PrintWriter(client.getOutputStream(), true)
                reb = DataOutputStream(client.getOutputStream())
                listenerSocket.isConnected(client.isConnected)

                while (client.isConnected && !client.isClosed) {
                    connectionIsSet = true
                    var bytebuffer: ByteArray
                    bytebuffer = ByteArray(100)
                    var rn = 0;
                    rn = client.getInputStream().read(bytebuffer)
                    println("rn = " + rn)
                    if (rn == -1) {
                        client.close()
                        break
                    }

                    for (i in 1..rn) {
                        if ((i - 2) >= 0 && bytebuffer.get(i - 1).toChar() == '\n' && bytebuffer.get(i - 2).toChar() == '\r') {
                            messageByte = ByteArray(message.size)
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
                    /*messageByte = ByteArray(message.size)
                    for (t in 1..message.size) {
                        messageByte.set(t - 1, message.get(t - 1))
                    }
                    listenerSocket.getListenerSocket(messageByte)
                    message.clear()*/

                }
            } else {
                listenerSocket.isConnected(false)
            }


            // client.close()
        } catch (e: UnknownHostException) {
            listenerSocket.failedBindSocket(e.message)

            println("---------------------------------------1" + e.message)
        } catch (e: IOException) {
            listenerSocket.failedBindSocket(e.message)

            println("---------------------------------------2" + e.message)

        }
        listenerSocket.isConnected(false)

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
                val end =  IntArray(2)
                end[0] = 0x0D
                end[1] = 0x0A
                var index = 0
                val byteArray = ByteArray((array.size * 4) + end.size * 4)

                for (i in 1..array.size){
                    val byteBuffer = ByteBuffer.allocate(4).putInt(array[i - 1]).array()
                    for (j in 1..byteBuffer.size){
                        byteArray.set(index, byteBuffer.get(byteBuffer.size - j))
                        index++
                    }
                }
                for (i in 1..end.size){
                    val byteBuffer = ByteBuffer.allocate(4).putInt(end[i - 1]).array()
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
    fun isConnected(boolean: Boolean)
}
package com.project.barde.barde.static

import java.io.*
import java.net.Socket
import java.net.UnknownHostException

/**
 * Created by michael on 08/06/2018.
 */
class SocketServer (val listenerSocket : ListenerSocket) : Runnable {
    private lateinit var rec : PrintWriter
    private lateinit var get : BufferedReader
    private lateinit var client: Socket
    private lateinit var buffer : String
    var message : MutableList<Byte>  = arrayListOf()
    var j = 0
    override fun run() {
        try {
                client = Socket("192.168.1.36", 23)
                println("connected")
                message.clear()
                get = BufferedReader(InputStreamReader(client.getInputStream()))
                rec = PrintWriter(client.getOutputStream(), true)
            while (true){
                /*val msg = mutableListOf<Char>()
                var buf = CharArray(200)
                var error = get.read(buf)
                println("read = " + buf.size )
                for (i in 1..buf.size){
                    if (buf.get(i - 1) == '\n' && buf.get(i - 2) == '\r'){
                        j = 0;
                        println("message2 = " + msg)
                        listenerSocket.getListenerSocket(msg)
                        msg.clear()
                    }else{
                        msg.add(buf.get(i - 1))
                        j++

                    }
                }*/
                var bytebuffer : ByteArray
                bytebuffer = ByteArray(200)
                var rn = 0;
                rn = client.getInputStream().read(bytebuffer)
                if (rn == -1){
                    client.close()
                    return
                }
                for(i in 1..rn){
                    if (rn > 1 && bytebuffer.get(i - 1).toChar() == '\n' && bytebuffer.get(i - 2).toChar() == '\r'){
                        var messageByte = ByteArray(message.size)
                        for (t in 1..message.size){
                            messageByte.set(t -1, message.get(t -1))
                        }
                        listenerSocket.getListenerSocket(messageByte)
                        message.clear()
                    }
                    else if (bytebuffer.get(i - 1).toChar() != '\n' && bytebuffer.get(i - 1).toChar() != '\r'){
                        message.add(bytebuffer.get(i - 1))
                        j++

                    }
                }
                /*var buffer = get.readLine()
                if (buffer.isNullOrEmpty()){
                    client.close()
                    return
                }
                listenerSocket.getListenerSocket(buffer)*/
            }

            // client.close()
        } catch (e : UnknownHostException) {
            e.printStackTrace()
        } catch (e : IOException){
            e.printStackTrace()
        }
    }

    companion object {
        val MUSIQUEPARAM : Int = 0x1
        val STYLE: Int = 0x11
        val JAZZ: Int = 0x111
        val BLUES: Int = 0x211
        val CHORD: Int = 0x21
        val ARPEGE: Int = 0x31
        val DRUM: Int = 0x41
        val BPM: Int = 0x51

    }
    public  fun rec() : PrintWriter{
        return rec
    }
}
interface ListenerSocket {
    fun getListenerSocket(buffer : ByteArray)
}
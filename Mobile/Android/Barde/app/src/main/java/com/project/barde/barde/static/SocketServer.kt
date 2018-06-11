package com.project.barde.barde.static

import java.io.BufferedReader
import java.io.IOException
import java.io.InputStreamReader
import java.io.PrintWriter
import java.net.Socket
import java.net.UnknownHostException

/**
 * Created by michael on 08/06/2018.
 */
class SocketServer : Runnable {
    private lateinit var rec : PrintWriter
    private lateinit var get : BufferedReader
    private lateinit var client: Socket

    override fun run() {
        try {
                client = Socket("192.168.1.36", 23)
                println("connected")
                get = BufferedReader(InputStreamReader(client.getInputStream()))
                rec = PrintWriter(client.getOutputStream(), true)
            //val buffer = get.readLine()
            //println("message = " + buffer)

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
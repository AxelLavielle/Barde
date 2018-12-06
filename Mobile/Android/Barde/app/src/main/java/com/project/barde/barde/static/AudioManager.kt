    package com.project.barde.barde.static

import android.content.Context
import android.media.MediaPlayer
import android.os.Environment
import java.io.File
import java.io.FileOutputStream

class AudioBardeManager {
    companion object {
        var  mediaPlayer = MediaPlayer()
        var firstPlay = false
        var indexFile = 0
        var startingPreparing = false
        var path = Environment.getExternalStorageDirectory().toString();
        var directory = File(path  + "/.bardeMusique");
        var LengthOfTraks = mutableListOf<Int>()
        lateinit var serverSocket: SocketServer
        lateinit var thread : Thread
        var serverIsConnected = false
        fun reset(){
            mediaPlayer.release()
            mediaPlayer = MediaPlayer()
            firstPlay = false
            startingPreparing = false
            serverSocket.close()
            thread.interrupt()
            serverIsConnected = false
            directory.delete()
            indexFile = 0
            LengthOfTraks.clear()
        }
        fun init(){
            if (directory.isDirectory){
                var files = directory.listFiles()
                for (file in files){
                    file.delete()
                }
            }
            directory.delete()
        }
        fun createNewMidiFile(midi : ByteArray) : File{
            directory.mkdir()
            var file = File(directory, "trak" + indexFile.toString() + ".mid")
            var fos  = FileOutputStream(file)
            fos.write(midi)
            fos.close()
            println("path = " + file.absoluteFile)
            return file
        }
    }
}
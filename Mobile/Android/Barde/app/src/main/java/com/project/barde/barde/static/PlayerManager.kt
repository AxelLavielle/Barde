package com.project.barde.barde.static

import android.content.Context
import android.media.MediaPlayer
import android.net.Uri
import android.os.AsyncTask
import com.project.barde.barde.ui.fragments.GenerationFragment
import java.io.File

class PlayerManager {
    lateinit var _generationFragment: GenerationFragment
    var _listOfTracks  = mutableListOf<File>()
    var _listOfLengthOfTracks = mutableListOf<Int>()
    var _mediaPlayer = MediaPlayer()
    var currentIndex = 0
    var lengthTrack = 0
    var seekTo = 0
    constructor(file: File, generationFragment: GenerationFragment){
        _generationFragment = generationFragment
        _listOfTracks.add(0, file)
        _mediaPlayer.setDataSource(_listOfTracks.get(currentIndex).absolutePath)
        _mediaPlayer.setOnPreparedListener(_generationFragment)
        _mediaPlayer.prepareAsync()
        setNextTrack(_mediaPlayer)
    }

    fun setNextTrack(mediaPlayer: MediaPlayer){
        mediaPlayer.setOnCompletionListener {
            currentIndex++
            if (_listOfTracks.size - 1 > currentIndex){
                var newMediaPlayer = MediaPlayer()
                newMediaPlayer.setDataSource(_listOfTracks.get(currentIndex).absolutePath)
                newMediaPlayer.setOnPreparedListener(_generationFragment)
                it.release()
                _mediaPlayer = newMediaPlayer
                setNextTrack(_mediaPlayer)
                seekTo = 0
                newMediaPlayer.prepareAsync()
            }


        }

    }

    fun getTotalLength() : Int{
        return lengthTrack * _listOfTracks.size
    }

    fun addToCurrentPos() : Int{
        return  lengthTrack * currentIndex
    }

    fun isLastIndex() : Boolean{
        if (currentIndex + 3 > _listOfTracks.size) {
            return true
        }
        return false
    }


    fun playAtThisTrackAtThisTime(time : Int){
        currentIndex = time / lengthTrack
        if (_listOfTracks.size <= currentIndex){
            currentIndex = _listOfTracks.size - 1
        }
        if (currentIndex == 0){
            seekTo = time
        }else{
            seekTo = (lengthTrack * currentIndex) - time
        }
        _mediaPlayer.release()
        _mediaPlayer = MediaPlayer()
        // to remove
        if (currentIndex - 1 >= 0) {
            val file = File(_listOfTracks.get(currentIndex - 1).absolutePath)
            file.delete()
        }
        _mediaPlayer.setDataSource(_listOfTracks.get(currentIndex).absolutePath)
        _mediaPlayer.setOnPreparedListener(_generationFragment)
        _mediaPlayer.prepareAsync()
        setNextTrack(_mediaPlayer)
    }

    fun addNewTrack(file : File, index : Int){
        _listOfTracks.add(index, file)

    }
}
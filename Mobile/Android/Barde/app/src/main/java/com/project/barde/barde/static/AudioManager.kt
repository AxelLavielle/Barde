package com.project.barde.barde.static

import android.media.MediaPlayer

class AudioBardeManager {
    companion object {
        var  mediaPlayer = MediaPlayer()
        var firstPlay = false
        var startingPreparing = false
        fun reset(){
            mediaPlayer.release()
            mediaPlayer = MediaPlayer()
            firstPlay = false
            startingPreparing = false
        }
    }
}
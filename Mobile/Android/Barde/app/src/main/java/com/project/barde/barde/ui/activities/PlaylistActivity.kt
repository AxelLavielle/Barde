package com.project.barde.barde.ui.activities

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.support.v7.widget.LinearLayoutManager
import com.project.barde.barde.R
import com.project.barde.barde.adapter.MusicListAdapter
import kotlinx.android.synthetic.main.activity_playlist.*

class PlaylistActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
    super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_playlist)
        var musicList = arrayOf<String>("touch me", "nobody", "why not", "this is you", "hello world", "nobody",
                "why not", "this is you", "hello world", "nobody", "why not", "this is you", "hello world")
        val adapter = MusicListAdapter(musicList)
        list_music_playlist.layoutManager = LinearLayoutManager(this, LinearLayoutManager.VERTICAL, false)
        list_music_playlist.adapter = adapter

    }
}

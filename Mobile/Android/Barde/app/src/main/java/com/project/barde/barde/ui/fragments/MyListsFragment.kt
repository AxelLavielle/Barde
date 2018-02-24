package com.project.barde.barde.ui.fragments

import android.os.Bundle
import android.support.v4.app.Fragment
import android.support.v7.widget.LinearLayoutManager
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import com.project.barde.barde.R
import com.project.barde.barde.adapter.MusicListAdapter
import kotlinx.android.synthetic.main.activity_playlist.*


/**
 * Created by michael on 10/02/2018.
 */
class MyListsFragment : Fragment() {
    override fun onCreateView(inflater: LayoutInflater?, container: ViewGroup?, savedInstanceState: Bundle?): View? {
        val v = inflater!!.inflate(R.layout.fragment_my_lists, container, false)
        return v
    }
    override fun onViewCreated(view: View?, savedInstanceState: Bundle?) {
        var musicList = arrayOf<String>("touch me", "nobody", "why not", "this is you", "hello world", "nobody",
                "why not", "this is you", "hello world", "nobody", "why not", "this is you", "hello world")
        val adapter = MusicListAdapter(musicList)
        list_music_playlist.layoutManager = LinearLayoutManager(activity, LinearLayoutManager.VERTICAL, false)
        list_music_playlist.adapter = adapter
    }
}
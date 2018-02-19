package com.project.barde.barde.ui.fragments

import android.content.Intent
import android.support.v4.app.Fragment
import android.os.Bundle
import android.support.v7.widget.GridLayoutManager
import android.support.v7.widget.LinearLayoutManager
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import com.project.barde.barde.R
import com.project.barde.barde.adapter.PlaylistAdpter
import com.project.barde.barde.ui.activities.PlaylistActivity
import kotlinx.android.synthetic.main.fragment_playlist.*

/**
 * Created by michael on 17/02/2018.
 */
class PlaylistFragment : Fragment() , View.OnClickListener{
    override fun onClick(p0: View?) {
        startActivity(Intent(activity, PlaylistActivity::class.java))
    }

    override fun onCreateView(inflater: LayoutInflater?, container: ViewGroup?, savedInstanceState: Bundle?): View? {
        val v = inflater!!.inflate(R.layout.fragment_playlist, container, false)
        return v
    }

    override fun onViewCreated(view: View?, savedInstanceState: Bundle?) {
        var playlists = arrayOf<String>("detente", "travail", "etude", "vacance", "relaxation")
        val adapter = PlaylistAdpter(playlists, this)

        playlist_discover_reycler_view.layoutManager = LinearLayoutManager(activity, LinearLayoutManager.HORIZONTAL, false)
        playlist_discover_reycler_view.adapter = adapter

        playlist_style_reycler_view.layoutManager = LinearLayoutManager(activity, LinearLayoutManager.HORIZONTAL, false)
        playlist_style_reycler_view.adapter = adapter

        playlist_best_reycler_view.layoutManager = LinearLayoutManager(activity, LinearLayoutManager.HORIZONTAL, false)
        playlist_best_reycler_view.adapter = adapter
        super.onViewCreated(view, savedInstanceState)
    }
}
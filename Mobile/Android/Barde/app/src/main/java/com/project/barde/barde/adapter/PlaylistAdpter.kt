package com.project.barde.barde.adapter

import android.support.v7.widget.RecyclerView
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.LinearLayout
import android.widget.TextView
import com.project.barde.barde.R

/**
 * Created by michael on 17/02/2018.
 */
class PlaylistAdpter(val playlists: Array<String>, val itemOnClickListener: View.OnClickListener) : RecyclerView.Adapter<PlaylistAdpter.ViewHolder>() {

    class ViewHolder(itemview: View) : RecyclerView.ViewHolder(itemview){
        val playlistview = itemview.findViewById<LinearLayout>(R.id.front_playlist)
        val name = itemview.findViewById<TextView>(R.id.item_name)
    }
    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        val inflater = LayoutInflater.from(parent.context)
        val viewItem = inflater.inflate(R.layout.item_playlist, parent, false)
        return ViewHolder(viewItem)

    }

    override fun getItemCount(): Int {
        return playlists.size
    }

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        val playlist = playlists[position]
        holder.name.text = playlist
        holder.playlistview.tag = position
        holder.playlistview.setOnClickListener(itemOnClickListener)
    }
}
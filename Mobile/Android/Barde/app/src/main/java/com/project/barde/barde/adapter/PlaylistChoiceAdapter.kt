package com.project.barde.barde.adapter

import android.support.v7.widget.RecyclerView
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.LinearLayout
import android.widget.TextView
import com.project.barde.barde.R

/**
 * Created by michael on 24/02/2018.
 */
class PlaylistChoiceAdapter(val playlists: Array<String>) : RecyclerView.Adapter<PlaylistChoiceAdapter.ViewHolder>() {
    class ViewHolder(itemview: View) : RecyclerView.ViewHolder(itemview){
        val name = itemview.findViewById<TextView>(R.id.item_creator)
    }
    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        val inflater = LayoutInflater.from(parent.context)
        val viewItem = inflater.inflate(R.layout.item_playlist_choice, parent, false)
        return ViewHolder(viewItem)

    }

    override fun getItemCount(): Int {
        return playlists.size
    }

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        val playlist = playlists[position]
        holder.name.text = playlist
    }
}
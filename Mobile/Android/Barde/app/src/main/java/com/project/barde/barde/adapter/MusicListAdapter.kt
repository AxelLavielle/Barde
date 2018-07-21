package com.project.barde.barde.adapter

import android.support.v7.widget.RecyclerView
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import com.project.barde.barde.R


/**
 * Created by michael on 18/02/2018.
 */
class MusicListAdapter(val musicList : Array<String>) :  RecyclerView.Adapter<MusicListAdapter.ViewHolder>(){

    class ViewHolder(itemView : View): RecyclerView.ViewHolder(itemView){

    }
    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        val inflater = LayoutInflater.from(parent.context)
        val viewItem = inflater.inflate(R.layout.item_music_list, parent, false)
        return ViewHolder(viewItem)
    }

    override fun getItemCount(): Int {
        return musicList.size
    }

    override fun onBindViewHolder(holder: ViewHolder?, position: Int) {

    }
}
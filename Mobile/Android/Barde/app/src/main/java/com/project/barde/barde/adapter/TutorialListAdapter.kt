package com.project.barde.barde.adapter

import android.support.v7.widget.AppCompatImageView
import android.support.v7.widget.AppCompatTextView
import android.support.v7.widget.RecyclerView
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.LinearLayout
import android.widget.TextView
import com.project.barde.barde.R
import com.project.barde.barde.model.TutoPage

class TutorialListAdapter(val tutorialList : List<TutoPage>): RecyclerView.Adapter<TutorialListAdapter.ViewHolder>() {
    class ViewHolder(itemview: View) : RecyclerView.ViewHolder(itemview){
        val title = itemview.findViewById<AppCompatTextView>(R.id.tutorial_list_item_view_title)
        val subtitle = itemview.findViewById<AppCompatTextView>(R.id.tutorial_list_item_view_subtitle)
        val image = itemview.findViewById<AppCompatImageView>(R.id.tutorial_list_item_view_image)
        val text = itemview.findViewById<AppCompatTextView>(R.id.tutorial_list_item_view_text)
    }
    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        val inflater = LayoutInflater.from(parent.context)
        val viewItem = inflater.inflate(R.layout.tutorial_list_item_view, parent, false)
        return ViewHolder(viewItem)

    }

    override fun getItemCount(): Int {
        return tutorialList.size
    }

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        val tutorial = tutorialList[position]
        holder.title.text = tutorial.title
        holder.subtitle.text = tutorial.subTitle
        holder.image.background = tutorial.imageId
        holder.text.text = tutorial.text
    }
}
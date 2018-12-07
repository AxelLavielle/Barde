package com.project.barde.barde.adapter

import android.support.v7.widget.RecyclerView
import android.view.View
import android.view.ViewGroup
import com.project.barde.barde.ui.view.*

class GenerationAdapter(val list: List<Any>) : RecyclerView.Adapter<GenerationAdapter.ViewHolder>() {
    companion object {
        val RADIO = 0
        val BUTTON = 1
        val SEEk_BAR = 2
    }

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        val item = list[position]
        val viewType = holder.itemViewType
        when (viewType) {
            RADIO -> (holder.itemView as RadioListItemView).setContent(item as RadioModel)
            BUTTON -> (holder.itemView as ChoiceListItemView).setContent(item as ChoiceModel)
            SEEk_BAR -> (holder.itemView as SlideBarListItemView).setContent(item as SlideModel)
            else -> {
                (holder as RadioListItemView).setContent(item as RadioModel)
            }
        }

    }

    class ViewHolder(itemview: View) : RecyclerView.ViewHolder(itemview) {
    }


    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): GenerationAdapter.ViewHolder {

        val view = when (viewType) {
            RADIO -> RadioListItemView(parent.context)
            BUTTON -> ChoiceListItemView(parent.context)
            SEEk_BAR -> SlideBarListItemView(parent.context)
            else -> {
                RadioListItemView(parent.context)
            }
        }
        view.layoutParams = ViewGroup.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT,
                ViewGroup.LayoutParams.MATCH_PARENT
        )

        return GenerationAdapter.ViewHolder(view)
    }

    override fun getItemCount(): Int {
        return list.size
    }

    override fun getItemViewType(position: Int): Int {
        return when (list[position]) {
            is ChoiceModel -> BUTTON
            is RadioModel -> RADIO
            is SlideModel -> SEEk_BAR
            else -> -1
        }
    }
}
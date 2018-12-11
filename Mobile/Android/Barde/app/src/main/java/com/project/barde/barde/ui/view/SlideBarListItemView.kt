package com.project.barde.barde.ui.view

import android.content.Context
import android.support.constraint.ConstraintLayout
import android.util.AttributeSet
import android.view.LayoutInflater
import android.view.View
import android.widget.SeekBar
import com.project.barde.barde.R
import com.project.barde.barde.static.AudioBardeManager
import com.project.barde.barde.ui.fragments.GenerationFragment
import kotlinx.android.synthetic.main.fragment_generation.*
import kotlinx.android.synthetic.main.slide_bar_list_item_view.view.*

data class SlideModel(val title: String, val min: Float, val max: Float, val unit : String, val value: Int)

class SlideBarListItemView @JvmOverloads constructor(
        context: Context, attrs: AttributeSet? = null, defStyleAttr: Int = 0
) : ConstraintLayout(context, attrs, defStyleAttr) {
    var mMax = 200.0f
    var mMin = 70.0f
    var m: Float = (mMax - mMin) / 100.0f
    var p = 0.0f
    var mValue = 0
    init {
        LayoutInflater.from(context).inflate(R.layout.slide_bar_list_item_view, this, true)

    }

    fun setContent(slideModel: SlideModel) {
        mMax = slideModel.max
        mMin = slideModel.min
        mValue = slideModel.min.toInt()
        m = (mMax - mMin) / 100.0f
        slide_bar_list_item_view_title.text = slideModel.title
        slide_bar_list_item_view_min.text = slideModel.min.toInt().toString()
        slide_bar_list_item_view_max.text = slideModel.max.toInt().toString()
        slide_bar_list_item_view_value.text = mValue.toInt().toString()
        slide_bar_list_item_view_unit.text = slideModel.unit
        slide_bar_list_item_view_seek_bar.setOnSeekBarChangeListener(object : SeekBar.OnSeekBarChangeListener {

            override fun onStartTrackingTouch(p0: SeekBar?) {
            }

            override fun onStopTrackingTouch(p0: SeekBar?) {
                AudioBardeManager.serverSocket.sendToServer(intArrayOf(GenerationFragment.MUSIQUEPARAM, GenerationFragment.BMP, p.toInt()))
            }

            override fun onProgressChanged(seekBar: SeekBar, progress: Int, fromUser: Boolean) {
                p = (m * progress) + mMin

                slide_bar_list_item_view_value.text = (p.toInt().toString())
            }
        })
    }
}
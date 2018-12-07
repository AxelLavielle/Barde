package com.project.barde.barde.ui.view

import android.content.Context
import android.graphics.Color
import android.support.constraint.ConstraintLayout
import android.util.AttributeSet
import android.util.TypedValue
import android.view.Gravity
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.LinearLayout
import com.project.barde.barde.R
import com.project.barde.barde.static.AudioBardeManager
import com.project.barde.barde.ui.fragments.GenerationFragment
import kotlinx.android.synthetic.main.choice_list_item_view.view.*

data class ChoiceModel(val title: String, val subtitle: String, val instrumentList: List<GenerationFragment.Instrument>,val codeAdd: Int, val codeRm: Int, val type: String)

class ChoiceListItemView @JvmOverloads constructor(
        context: Context, attrs: AttributeSet? = null, defStyleAttr: Int = 0
) : ConstraintLayout(context, attrs, defStyleAttr) {
    init {
        LayoutInflater.from(context).inflate(R.layout.choice_list_item_view, this, true)
    }

    fun setContent(choiceModel: ChoiceModel) {
        choice_list_itemm_view_title.text = choiceModel.title
        choice_list_itemm_view_subtitle.text = choiceModel.subtitle
        var ln = findViewById<LinearLayout>(R.id.list_instrument_generation_chords)
        ln?.removeAllViews()

        val margin = TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_PX, 10.toFloat(), getResources().getDisplayMetrics()).toInt()

        val params = LinearLayout.LayoutParams(
                LinearLayout.LayoutParams.MATCH_PARENT,
                LinearLayout.LayoutParams.WRAP_CONTENT)
        params.setMargins(margin, margin, margin, margin)

        ln?.gravity = Gravity.CENTER
        for (instrument in choiceModel.instrumentList) {
            var button = Button(context)
            button.text = instrument.name
            //button.textSize = TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, 9.toFloat(), getResources().getDisplayMetrics())
            if (instrument.isSelected) {
                button.setBackgroundResource(R.drawable.button_selection_generation_selected)
                button.setTextColor(Color.parseColor("#CA5E85"))
            } else {
                button.setTextColor(Color.parseColor("#FFFFFF"))
                button.setBackgroundResource(R.drawable.button_selection_generation)
            }
            button.layoutParams = params
            button.textAlignment = View.TEXT_ALIGNMENT_CENTER
            ln?.addView(button)
            button.setOnClickListener {
                println("le code est = " + GenerationFragment.MUSIQUEPARAM + " " + instrument.code + " " + choiceModel.codeRm)
                if (instrument.isSelected) {
                    if (instrument.drum) {
                        AudioBardeManager.serverSocket.sendToServer(intArrayOf(GenerationFragment.MUSIQUEPARAM, instrument.code, choiceModel.codeRm))
                    } else {
                        AudioBardeManager.serverSocket.sendToServer(intArrayOf(GenerationFragment.MUSIQUEPARAM, choiceModel.codeRm, instrument.code))
                    }

                } else {
                    if (instrument.drum) {
                        AudioBardeManager.serverSocket.sendToServer(intArrayOf(GenerationFragment.MUSIQUEPARAM, instrument.code, choiceModel.codeAdd))
                    } else {
                        AudioBardeManager.serverSocket.sendToServer(intArrayOf(GenerationFragment.MUSIQUEPARAM, choiceModel.codeAdd, instrument.code))
                    }

                }
                instrument.setButton(button)

                /* to remove */
                //println("isplayer = " + mediaPlayer?.isPlaying)


                /* -------- */
            }
        }


    }
}
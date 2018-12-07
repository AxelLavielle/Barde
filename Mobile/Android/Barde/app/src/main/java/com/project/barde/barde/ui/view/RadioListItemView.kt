package com.project.barde.barde.ui.view

import android.content.Context
import android.graphics.Color
import android.graphics.Paint
import android.support.constraint.ConstraintLayout
import android.util.AttributeSet
import android.util.TypedValue
import android.view.Gravity
import android.view.LayoutInflater
import android.view.View
import android.widget.Button
import android.widget.LinearLayout
import android.widget.RadioButton
import android.widget.RadioGroup
import com.project.barde.barde.R
import com.project.barde.barde.static.AudioBardeManager
import com.project.barde.barde.ui.fragments.GenerationFragment
import kotlinx.android.synthetic.main.radio_choice_list_item_view.view.*
import org.jetbrains.anko.custom.style


data class RadioModel(val title: String, val radioList: List<GenerationFragment.Style>)

class RadioListItemView @JvmOverloads constructor(
        context: Context, attrs: AttributeSet? = null, defStyleAttr: Int = 0
) : ConstraintLayout(context, attrs, defStyleAttr) {

    init {
        LayoutInflater.from(context).inflate(R.layout.radio_choice_list_item_view, this, true)
    }

    fun setContent(radioModel: RadioModel) {
        radio_choice_list_item_view_title.text = radioModel.title
        val rg = findViewById<RadioGroup>(R.id.radio_choice_list_item_view_radio_group)

        rg?.removeAllViews()

        val margin = TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_PX, 10.toFloat(), getResources().getDisplayMetrics()).toInt()

        val params = LinearLayout.LayoutParams(
                LinearLayout.LayoutParams.MATCH_PARENT,
                LinearLayout.LayoutParams.WRAP_CONTENT)
        params.setMargins(margin, margin, margin, margin)

        rg?.gravity = Gravity.CENTER
        for (style in radioModel.radioList) {
            val rd = RadioButton(context)
            rd.buttonDrawable = null
            rd.text = style.name
            if (style.isSelected) {
                rd.setBackgroundResource(R.drawable.button_selection_generation_selected)
                rd.setTextColor(Color.parseColor("#CA5E85"))
            } else {
                rd.setTextColor(Color.parseColor("#FFFFFF"))
                rd.setBackgroundResource(R.drawable.button_selection_generation)
            }
            rd.layoutParams = params
            rd.textAlignment = View.TEXT_ALIGNMENT_CENTER
            rd.setOnClickListener {
                AudioBardeManager.serverSocket.sendToServer(style.code)
            }
            rg.addView(rd)
            style.setButton(rd)
        }
    }


}
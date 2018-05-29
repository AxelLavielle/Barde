package com.project.barde.barde.ui.fragments

import android.content.ContentValues.TAG
import android.graphics.Color
import android.media.AudioManager
import android.media.MediaPlayer
import android.net.Uri
import android.os.Bundle
import android.support.v4.app.Fragment
import android.support.v7.app.AlertDialog
import android.support.v7.widget.LinearLayoutManager
import android.support.v7.widget.RecyclerView
import android.util.Log
import android.util.TypedValue
import android.view.Gravity
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.*
import com.project.barde.barde.R
import com.project.barde.barde.adapter.PlaylistChoiceAdapter
import kotlinx.android.synthetic.main.dialog_playlist_choice.*
import kotlinx.android.synthetic.main.fragment_generation.*

/**
 * Created by michael on 17/02/2018.
 */
class GenerationFragment : Fragment() {
    //private val fluxAudio = "http://5.135.160.60:3333/test"
    private val fluxAudio = "http://cdn.nrjaudio.fm/audio1/fr/30001/mp3_128.mp3?origine=fluxradioss"
    data class Instrument(val name: String, var isSelected: Boolean)
    val listOfInstruementChords = listOf<Instrument>(Instrument("Acoustic Grand piano", false), Instrument("Trumpet", false),
            Instrument("Soprano Sax", false))
    val listOfInstruementArpeges = listOf<Instrument>(Instrument("Acoustic Grand piano", false), Instrument("Trumpet", false),
            Instrument("Soprano Sax", false))
    val listOfInstruement = listOf<Instrument>(Instrument("Drums", false))
    var  mediaPlayer = MediaPlayer()
    var pianoSelected = true
    var fluteSelected = false
    var batterieSelected = false
    var index = 0
    var lastindex = 0
    var firstPlay = true
    override fun onCreateView(inflater: LayoutInflater?, container: ViewGroup?, savedInstanceState: Bundle?): View? {


        return inflater!!.inflate(R.layout.fragment_generation, container, false)
    }
    override fun onViewCreated(view: View?, savedInstanceState: Bundle?) {
        var listOfChoice = listOf<LinearLayout>(style_choice_genearation, instrument_choice_generation_chords,
                instrument_choice_generation_arpeges, instrument_choice_generation, rythme_choice_genaration)
        var listOfPanination = listOf<TextView>(pagination_style, pagination_instruments, pagination_bpm)
        /*add_to_playlist.setOnClickListener {
            add_to_playlist()
        }*/
        next_button_generation.visibility = View.VISIBLE
        previous_button_generation.visibility = View.VISIBLE

        viewSelectButtonGeneration(listOfInstruementChords, R.id.list_instrument_generation_chords)
        viewSelectButtonGeneration(listOfInstruementArpeges, R.id.instrument_choice_generation_arpeges)
        viewSelectButtonGeneration(listOfInstruement, R.id.instrument_choice_generation)

        listOfPanination.get(index).setBackgroundResource(R.drawable.rounded_background_white)
        listOfPanination.get(index).setTextColor(Color.parseColor("#CA5E85"))
        if (index == 0){
            listOfChoice.get(0).visibility = View.VISIBLE
            previous_button_generation.visibility = View.INVISIBLE
        }else{
            listOfChoice.get(index).visibility = View.VISIBLE
            if (index >= listOfChoice.size - 1){
                next_button_generation.visibility = View.INVISIBLE
            }
        }


        next_button_generation.setOnClickListener{
            if (index < (listOfChoice.size - 1)){
                lastindex = index
                index++
                listOfChoice.get(lastindex).visibility = View.GONE
                listOfChoice.get(index).visibility = View.VISIBLE
                previous_button_generation.visibility = View.VISIBLE
                if (index >= (listOfChoice.size - 1)){
                    next_button_generation.visibility = View.INVISIBLE
                }
            }
        }

        previous_button_generation.setOnClickListener{
            if (index > 0){
                lastindex = index
                index--
                listOfChoice.get(lastindex).visibility = View.GONE
                listOfChoice.get(index).visibility = View.VISIBLE
                next_button_generation.visibility = View.VISIBLE
                if (index <= 0){
                    previous_button_generation.visibility = View.INVISIBLE
                }
            }
        }


        println("uri = " + Uri.parse(fluxAudio))
        if (firstPlay == true){
            firstPlay = false
            mediaPlayer.setDataSource(fluxAudio)
            mediaPlayer.prepare()
        }

        if (mediaPlayer.isPlaying){
            button_generation.setImageResource(R.drawable.ic_pause_circle_filled_white_48dp)
        }else{
            button_generation.setImageResource(R.drawable.ic_play_circle_filled_white_white_48dp)
        }
        button_generation.setOnClickListener{

            println("uri = click")
            println("uri = looping " + mediaPlayer.isLooping)
            println("uri = playing " + mediaPlayer.isPlaying)
            if (mediaPlayer.isPlaying){
                println("uri =  pause")
                mediaPlayer.pause()
                button_generation.setImageResource(R.drawable.ic_play_circle_filled_white_white_48dp)
            }else{
                mediaPlayer.start()
                println("uri = duraition ")
                button_generation.setImageResource(R.drawable.ic_pause_circle_filled_white_48dp)
            }
        }


        style_button_radio.setOnCheckedChangeListener { radioGroup, i ->
            jazz_style_radio.setBackgroundResource(R.drawable.button_selection_generation)
            jazz_style_radio.setTextColor(Color.WHITE)
            blues_style_radio.setBackgroundResource(R.drawable.button_selection_generation)
            blues_style_radio.setTextColor(Color.WHITE)
            if (jazz_style_radio.isChecked){
                jazz_style_radio.setBackgroundResource(R.drawable.button_selection_generation_selected)
                jazz_style_radio.setTextColor(Color.parseColor("#CA5E85"))
            }else if (blues_style_radio.isChecked){
                blues_style_radio.setBackgroundResource(R.drawable.button_selection_generation_selected)
                blues_style_radio.setTextColor(Color.parseColor("#CA5E85"))

            }
        }

        seek_bar_bpm.setProgress(22)
        seek_bar_bpm.setOnSeekBarChangeListener(object : SeekBar.OnSeekBarChangeListener {
            override fun onStartTrackingTouch(p0: SeekBar?) {
            }

            override fun onStopTrackingTouch(p0: SeekBar?) {
            }

            override fun onProgressChanged(seekBar: SeekBar, progress: Int, fromUser: Boolean) {
                var p = (0.9 * progress) + 60

                value_bpm.text = p.toInt().toString()
            }
        })

    }

    fun viewSelectButtonGeneration(list: List<Instrument>, id : Int){
        var ln = view?.findViewById<LinearLayout>(id)
        val margin = TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, 5.toFloat(), getResources().getDisplayMetrics()).toInt()
        val params = LinearLayout.LayoutParams(
                TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, 180.toFloat(), getResources().getDisplayMetrics()).toInt(),
                TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, 30.toFloat(), getResources().getDisplayMetrics()).toInt()
        )
        /*params.setMargins(margin, margin, margin, margin)*/
        ln?.setLayoutParams(LinearLayout.LayoutParams(
                LinearLayout.LayoutParams.MATCH_PARENT,
                LinearLayout.LayoutParams.WRAP_CONTENT,
                1.0f
        ))
        //ln?.gravity = Gravity.CENTER
        for (instrument in list){
            var button = Button(context)
            button.text = instrument.name
            button.textSize = TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, 9.toFloat(), getResources().getDisplayMetrics())
            button.setTextColor(Color.parseColor("#FFFFFF"))
            //button.layoutParams = params
            button.textAlignment = View.TEXT_ALIGNMENT_CENTER
            button.setBackgroundResource(R.drawable.button_selection_generation)
            ln?.addView(button)
            button.setOnClickListener{
                if (instrument.isSelected){
                    instrument.isSelected = false
                    button.setBackgroundResource(R.drawable.button_selection_generation)
                    button.setTextColor(Color.WHITE)
                }else{
                    instrument.isSelected = true
                    button.setBackgroundResource(R.drawable.button_selection_generation_selected)
                    button.setTextColor(Color.parseColor("#CA5E85"))
                }
            }
        }
    }

    fun add_to_playlist(){
        val builder = AlertDialog.Builder(activity)
        val inflater = layoutInflater
        val view = inflater.inflate(R.layout.dialog_playlist_choice, null)
        var playlists = arrayOf<String>("detente", "travail", "etude", "vacance", "relaxation", "travail", "etude", "vacance", "relaxation", "travail", "etude", "vacance", "relaxation", "travail", "etude", "vacance", "relaxation", "travail", "etude", "vacance", "relaxation", "travail", "etude", "vacance", "relaxation")
        val adapter = PlaylistChoiceAdapter(playlists)
        val recyclerView = view.findViewById<RecyclerView>(R.id.playlist_reycler_view)
        recyclerView.layoutManager = LinearLayoutManager(activity)
        recyclerView.adapter = adapter
        builder.setView(view)
        val dialog = builder.create()
        dialog.show()
    }
}
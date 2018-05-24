package com.project.barde.barde.ui.fragments

import android.graphics.Color
import android.media.AudioManager
import android.media.MediaPlayer
import android.net.Uri
import android.os.Bundle
import android.support.v4.app.Fragment
import android.support.v7.app.AlertDialog
import android.support.v7.widget.LinearLayoutManager
import android.support.v7.widget.RecyclerView
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
    private val fluxAudio = "http://cdn.nrjaudio.fm/audio1/fr/30001/mp3_128.mp3?origine=fluxradios"
    lateinit var mediaPlayer : MediaPlayer
    var pianoSelected = true
    var fluteSelected = false
    var batterieSelected = false
    var index = 0
    var lastindex = 0
    override fun onCreateView(inflater: LayoutInflater?, container: ViewGroup?, savedInstanceState: Bundle?): View? {
        return inflater!!.inflate(R.layout.fragment_generation, container, false)
    }
    override fun onViewCreated(view: View?, savedInstanceState: Bundle?) {
        var listOfChoice = listOf<LinearLayout>(style_choice_genearation, instrument_choice_generation, rythme_choice_genaration)
        var listOfPanination = listOf<TextView>(pagination_style, pagination_instruments, pagination_bpm)
        /*add_to_playlist.setOnClickListener {
            add_to_playlist()
        }*/
        next_button_generation.visibility = View.VISIBLE
        previous_button_generation.visibility = View.VISIBLE
        if (!pianoSelected){
            piano_button_generation.setBackgroundResource(R.drawable.button_selection_generation)
            piano_button_generation.setTextColor(Color.WHITE)
        }else{
            piano_button_generation.setBackgroundResource(R.drawable.button_selection_generation_selected)
            piano_button_generation.setTextColor(Color.parseColor("#CA5E85"))
        }
        if (!fluteSelected){
            flute_button_generation.setBackgroundResource(R.drawable.button_selection_generation)
            flute_button_generation.setTextColor(Color.WHITE)
        }else{
            flute_button_generation.setBackgroundResource(R.drawable.button_selection_generation_selected)
            flute_button_generation.setTextColor(Color.parseColor("#CA5E85"))
        }
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

        if (!batterieSelected){
            batterie_button_generation.setBackgroundResource(R.drawable.button_selection_generation)
            batterie_button_generation.setTextColor(Color.WHITE)
        }else{
            batterie_button_generation.setBackgroundResource(R.drawable.button_selection_generation_selected)
            batterie_button_generation.setTextColor(Color.parseColor("#CA5E85"))
        }

        next_button_generation.setOnClickListener{
            if (index < (listOfChoice.size - 1)){
                lastindex = index
                index++
                listOfPanination.get(index).setBackgroundResource(R.drawable.rounded_background_white)
                listOfPanination.get(index).setTextColor(Color.parseColor("#CA5E85"))
                listOfPanination.get(lastindex).setBackgroundColor(Color.parseColor("#CA5E85"))
                listOfPanination.get(lastindex).setTextColor(Color.WHITE)
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
                listOfPanination.get(index).setBackgroundResource(R.drawable.rounded_background_white)
                listOfPanination.get(index).setTextColor(Color.parseColor("#CA5E85"))
                listOfPanination.get(lastindex).setBackgroundColor(Color.parseColor("#CA5E85"))
                listOfPanination.get(lastindex).setTextColor(Color.WHITE)
                listOfChoice.get(lastindex).visibility = View.GONE
                listOfChoice.get(index).visibility = View.VISIBLE
                next_button_generation.visibility = View.VISIBLE
                if (index <= 0){
                    previous_button_generation.visibility = View.INVISIBLE
                }
            }
        }


        /*println(Uri.parse(fluxAudio))
        mediaPlayer = MediaPlayer.create(context, Uri.parse(fluxAudio))
        button_generation.setOnClickListener{
            if (mediaPlayer.isPlaying){
                mediaPlayer.pause()
                button_generation.setImageResource(R.drawable.ic_play_circle_filled_white_white_48dp)
            }else{
                mediaPlayer.start()
                button_generation.setImageResource(R.drawable.ic_pause_circle_filled_white_48dp)
            }
        }*/


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

        piano_button_generation.setOnClickListener{
            if (pianoSelected){
                pianoSelected = false
                piano_button_generation.setBackgroundResource(R.drawable.button_selection_generation)
                piano_button_generation.setTextColor(Color.WHITE)
            }else{
                pianoSelected = true
                piano_button_generation.setBackgroundResource(R.drawable.button_selection_generation_selected)
                piano_button_generation.setTextColor(Color.parseColor("#CA5E85"))
            }
        }
        flute_button_generation.setOnClickListener{
            if (fluteSelected){
                fluteSelected = false
                flute_button_generation.setBackgroundResource(R.drawable.button_selection_generation)
                flute_button_generation.setTextColor(Color.WHITE)
            }else{
                fluteSelected = true
                flute_button_generation.setBackgroundResource(R.drawable.button_selection_generation_selected)
                flute_button_generation.setTextColor(Color.parseColor("#CA5E85"))
            }
        }
        batterie_button_generation.setOnClickListener{
            if (batterieSelected){
                batterieSelected = false
                batterie_button_generation.setBackgroundResource(R.drawable.button_selection_generation)
                batterie_button_generation.setTextColor(Color.WHITE)
            }else{
                batterieSelected = true
                batterie_button_generation.setBackgroundResource(R.drawable.button_selection_generation_selected)
                batterie_button_generation.setTextColor(Color.parseColor("#CA5E85"))
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
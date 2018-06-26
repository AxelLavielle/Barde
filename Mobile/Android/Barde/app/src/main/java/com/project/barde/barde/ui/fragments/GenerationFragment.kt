package com.project.barde.barde.ui.fragments

import android.content.ContentValues.TAG
import android.content.Context.*
import android.graphics.Color
import android.media.AudioManager
import android.media.MediaPlayer
import android.net.Uri
import android.os.Bundle
import android.os.Environment
import android.os.NetworkOnMainThreadException
import android.provider.Telephony.Mms.Part.FILENAME
import android.support.v4.app.Fragment
import android.support.v7.app.AlertDialog
import android.support.v7.widget.LinearLayoutManager
import android.support.v7.widget.RecyclerView
import android.util.TypedValue
import android.view.Gravity
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.*
import com.github.kittinunf.fuel.core.requests.write
import com.project.barde.barde.R
import com.project.barde.barde.adapter.PlaylistChoiceAdapter
import com.project.barde.barde.static.ListenerSocket
import com.project.barde.barde.static.SocketServer
import kotlinx.android.synthetic.main.fragment_generation.*
import org.jetbrains.anko.doAsync
import java.io.*
import java.net.Socket
import java.net.UnknownHostException


/**
 * Created by michael on 17/02/2018.
 */
class GenerationFragment : Fragment(), MediaPlayer.OnPreparedListener, ListenerSocket {
    override fun getListenerSocket(buffer: ByteArray){
        //println("coucou je get " + buffer)
        if (buffer.size > 0 && buffer[0].toChar() != 'h'){
            try {
                var path = Environment.getExternalStorageDirectory().toString();
                var directory = File(path  + "/bardeMusique");
                directory.mkdir()
                var file = File(directory, "bbbbarde.mid")
                var modeAppend = false
                if (file.exists()){
                    if (firstPlay && !startingPreparing){
                        file.delete()
                        modeAppend = false
                    }else{
                        modeAppend = true
                    }
                }
                var fos  = FileOutputStream(file, modeAppend)
                fos.write(buffer)
                fos.close()
                var b = buffer.size
                var p = buffer[b - 1]
                println("la dernier valeur is " + buffer[b - 1] + " " + buffer[b - 2] + "efeufenuf voila")
                println("size = " + buffer.size   )
                //println("buffer add " + buffer)

                // println("size = " + buffer.length)
                //println("content = " + buffer.toByteArray())
                /*val fos = context.openFileOutput("test.mid", MODE_WORLD_READABLE)
                fos.write(buffer.toByteArray())
                fos.close()
                println("file created")*/
//                val file = File(context.filesDir.toString() + "/test.mid")
               /* file.setReadable(true, false)*/
                /*val bufferedReader = file.bufferedReader()
                val text:List<String> = bufferedReader.readLines()
                print("coucou je get ")
                for(line in text){
                    println(line)
                }*/
                //println("file path = " + context.filesDir.toString() + "/test.mid")


                if (firstPlay && !startingPreparing){
                    var fis = FileInputStream(file)
                    var fd = fis.getFD()
                    startingPreparing = true;

                    //mediaPlayer.setDataSource(context.filesDir.toString() +"/test.mid")
                    mediaPlayer.setDataSource(fd)
                    fis.close()

                    //mediaPlayer.setDataSource("/storage/emulated/0/file.mid")
                    mediaPlayer.setOnPreparedListener(this);
                    mediaPlayer.prepareAsync();
                    mediaPlayer.start()
                    //serverSocket.rec().println("S")
                }


            }catch (e : Exception){
                println("error = "+ e.message)
            }

        }
    }


    private val fluxAudio = "http://5.135.160.60:3333/test/mobile"
    //private val fluxAudio = "http://cdn.nrjaudio.fm/audio1/fr/30001/mp3_128.mp3?origine=fluxradioss"
    data class Instrument(val name: String, var isSelected: Boolean)
    val listOfInstruementChords = listOf<Instrument>(Instrument("Trumpet", false), Instrument("Piano", false),
            Instrument("Saxophone", false))
    val listOfInstruementArpeges = listOf<Instrument>(Instrument("Trumpet", false), Instrument("Piano", false),
            Instrument("Saxophone", false))
    val listOfInstruement = listOf<Instrument>(Instrument("Enabled drums", false))
    var  mediaPlayer = MediaPlayer()
    var pianoSelected = true
    var fluteSelected = false
    var batterieSelected = false
    var index = 0
    var lastindex = 0
    var firstPlay = false
    var serverPort = 23
    var serverIp = "192.168.1.36"
    val serverSocket = SocketServer(this)
    val thread = Thread(serverSocket)
    var startingPreparing = false;

    override fun onPrepared(p0: MediaPlayer) {
        button_generation.setImageResource(R.drawable.ic_pause_circle_filled_white_48dp)
        mediaPlayer.start()
        button_generation.isEnabled = true
    }
    override fun onCreateView(inflater: LayoutInflater?, container: ViewGroup?, savedInstanceState: Bundle?): View?  {

        return inflater!!.inflate(R.layout.fragment_generation, container, false)
    }
    override fun onViewCreated(view: View?, savedInstanceState: Bundle?) {
        var listOfChoice = listOf<LinearLayout>(style_choice_genearation, instrument_choice_generation_chords,
                instrument_choice_generation_arpeges, instrument_choice_generation, rythme_choice_genaration)
        var listOfPanination =  listOf<ImageView>(pagination_a, pagination_b, pagination_c, pagination_d, pagination_e)

        /*add_to_playlist.setOnClickListener {
            add_to_playlist()

        }*/
        if (thread.state == Thread.State.NEW){
            thread.start()
        }
        for (choice in listOfChoice){
            choice.visibility = View.GONE
        }

        next_button_generation.visibility = View.VISIBLE
        previous_button_generation.visibility = View.VISIBLE

        viewSelectButtonGeneration(listOfInstruementChords, R.id.list_instrument_generation_chords, "CHORDS")
        viewSelectButtonGeneration(listOfInstruementArpeges, R.id.list_instrument_generation_arpeges, "ARPEGES")
        viewSelectButtonGeneration(listOfInstruement, R.id.list_instrument_generation, "BPM")

        if (index == 0){
            listOfPanination.get(0).setImageResource(R.drawable.circle_full_pink)
            listOfChoice.get(0).visibility = View.VISIBLE
            previous_button_generation.visibility = View.INVISIBLE
        }else{
            listOfPanination.get(index).setImageResource(R.drawable.circle_full_pink)
            listOfChoice.get(index).visibility = View.VISIBLE
            if (index >= listOfChoice.size - 1){
                next_button_generation.visibility = View.INVISIBLE
            }
        }


        next_button_generation.setOnClickListener{
            if (index < (listOfChoice.size - 1)){
                lastindex = index
                index++
                listOfPanination.get(lastindex).setImageResource(R.drawable.circle_full_white)
                listOfPanination.get(index).setImageResource(R.drawable.circle_full_pink)
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
                listOfPanination.get(lastindex).setImageResource(R.drawable.circle_full_white)
                listOfPanination.get(index).setImageResource(R.drawable.circle_full_pink)
                listOfChoice.get(lastindex).visibility = View.GONE
                listOfChoice.get(index).visibility = View.VISIBLE
                next_button_generation.visibility = View.VISIBLE
                if (index <= 0){
                    previous_button_generation.visibility = View.INVISIBLE
                }
            }
        }


        println("uri = " + Uri.parse(fluxAudio))

        style_button_radio.setOnCheckedChangeListener { radioGroup, i ->
            /*jazz_style_radio.setBackgroundResource(R.drawable.button_selection_generation)
            jazz_style_radio.setTextColor(Color.WHITE)
            blues_style_radio.setBackgroundResource(R.drawable.button_selection_generation)
            blues_style_radio.setTextColor(Color.WHITE)
            if (jazz_style_radio.isChecked){
                //serverSocket.rec().println("MUSIQUEPARAM;STYLE;BLUE")
                jazz_style_radio.setBackgroundResource(R.drawable.button_selection_generation_selected)
                jazz_style_radio.setTextColor(Color.parseColor("#CA5E85"))
            }else if (blues_style_radio.isChecked){
                //serverSocket.rec().println("MUSIQUEPARAM;STYLE;JAZZ")
                blues_style_radio.setBackgroundResource(R.drawable.button_selection_generation_selected)
                blues_style_radio.setTextColor(Color.parseColor("#CA5E85"))

            }*/
        }
        seek_bar_bpm.setOnSeekBarChangeListener(object : SeekBar.OnSeekBarChangeListener {
            var max = 200.0f
            var min  = 70.0f
            var m : Float = (max - min) / 100.0f
            override fun onStartTrackingTouch(p0: SeekBar?) {
            }

            override fun onStopTrackingTouch(p0: SeekBar?) {
            }

            override fun onProgressChanged(seekBar: SeekBar, progress: Int, fromUser: Boolean) {
                var p = (m * progress) + min
                serverSocket.rec().println("MUSIQUEPARAM;BPM;" + p.toInt().toString())
                value_bpm.text = (p.toInt().toString() + " BPM")
            }
        })

        if (mediaPlayer.isPlaying){
            button_generation.setImageResource(R.drawable.ic_pause_circle_filled_white_48dp)
        }else{
            button_generation.setImageResource(R.drawable.ic_play_circle_filled_white_white_48dp)
        }
        button_generation.setOnClickListener {

            var builder = StringBuilder()
            builder.append('\u0002')
            builder.append('\u0000')
            builder.append('\u0012')
            builder.append('\u0012')
            builder.append('\u0012')
            builder.append('\u0012')
            builder.append('\u0012')
            println("message = " + builder.toString())
            //serverSocket.rec().println(builder.toString())
            if (firstPlay){
                serverSocket.rec().println("S")
                button_generation.setImageResource(R.drawable.ic_play_circle_filled_white_white_48dp)
                firstPlay = false
                if (mediaPlayer.isPlaying){
                    mediaPlayer.pause()
                    startingPreparing = false;
                }
            }else{
                serverSocket.rec().println("P")
                firstPlay = true
                button_generation.setImageResource(R.drawable.ic_pause_circle_filled_white_48dp)
            }
           /* try {
                if (firstPlay == true) {
                    mediaPlayer.setDataSource(fluxAudio)
                    mediaPlayer.setOnPreparedListener(this);
                    mediaPlayer.prepareAsync();
                    button_generation.setImageResource(R.drawable.ic_loading_white_24dp)
                    button_generation.isEnabled = false
                    firstPlay = false
                } else if (mediaPlayer.isPlaying) {
                    println("uri =  pause")
                    mediaPlayer.pause()
                    button_generation.setImageResource(R.drawable.ic_play_circle_filled_white_white_48dp)
                } else {
                    mediaPlayer.start()
                    println("uri = duraition ")
                    button_generation.setImageResource(R.drawable.ic_pause_circle_filled_white_48dp)
                }
            } catch (e: Exception) {
                println("error = " + e.message)
            }*/
        }

        seek_bar_bpm.setProgress(0)

    }

    fun viewSelectButtonGeneration(list: List<Instrument>, id : Int, type: String){
        var ln = view?.findViewById<LinearLayout>(id)
        val margin = TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_PX, 10.toFloat(), getResources().getDisplayMetrics()).toInt()
        /*val params = LinearLayout.LayoutParams(
                TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, 180.toFloat(), getResources().getDisplayMetrics()).toInt(),
                TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, 30.toFloat(), getResources().getDisplayMetrics()).toInt()
        )*/
        val params = LinearLayout.LayoutParams(
                LinearLayout.LayoutParams.MATCH_PARENT,
                LinearLayout.LayoutParams.WRAP_CONTENT)
        params.setMargins(margin, margin, margin, margin)
        ln?.setLayoutParams(LinearLayout.LayoutParams(
                LinearLayout.LayoutParams.MATCH_PARENT,
                LinearLayout.LayoutParams.WRAP_CONTENT,
                1.0f
        ))
        ln?.gravity = Gravity.CENTER
        for (instrument in list){
            var button = Button(context)
            button.text = instrument.name
            //button.textSize = TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, 9.toFloat(), getResources().getDisplayMetrics())
            if (instrument.isSelected){
                button.setBackgroundResource(R.drawable.button_selection_generation_selected)
                button.setTextColor(Color.parseColor("#CA5E85"))
            }else{
                button.setTextColor(Color.parseColor("#FFFFFF"))
                button.setBackgroundResource(R.drawable.button_selection_generation)
            }
            button.layoutParams = params
            button.textAlignment = View.TEXT_ALIGNMENT_CENTER
            ln?.addView(button)
            button.setOnClickListener{
                if (instrument.isSelected){
                    instrument.isSelected = false
                    button.setBackgroundResource(R.drawable.button_selection_generation)
                    button.setTextColor(Color.WHITE)
                }else{
                    serverSocket.rec().println("MUSIQUEPARAM;" + type + ":" + instrument.name.toUpperCase())
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

    override fun onDestroy() {
        super.onDestroy()
    }
}
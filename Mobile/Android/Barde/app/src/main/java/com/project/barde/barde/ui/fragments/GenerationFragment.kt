package com.project.barde.barde.ui.fragments

import android.Manifest
import android.content.pm.PackageManager
import android.graphics.Color
import android.media.MediaPlayer
import android.os.Bundle
import android.os.Environment
import android.os.Handler
import android.support.v4.app.ActivityCompat
import android.support.v4.app.Fragment
import android.support.v4.content.ContextCompat
import android.support.v7.app.AlertDialog
import android.support.v7.widget.LinearLayoutManager
import android.support.v7.widget.RecyclerView
import android.util.TypedValue
import android.view.Gravity
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.*
import com.project.barde.barde.R
import com.project.barde.barde.adapter.PlaylistChoiceAdapter
import com.project.barde.barde.static.AudioBardeManager
import com.project.barde.barde.static.ListenerSocket
import com.project.barde.barde.static.SocketServer
import kotlinx.android.synthetic.main.fragment_generation.*
import org.jetbrains.anko.doAsync
import java.io.*
import java.util.concurrent.TimeUnit


/**
 * Created by michael on 17/02/2018.
 */
class GenerationFragment : Fragment(), MediaPlayer.OnPreparedListener, ListenerSocket {


    data class Instrument(val name: String, var isSelected: Boolean, var code: Int)
    val listOfInstruementChords = listOf<Instrument>(Instrument("Trumpet", false, 57), Instrument("Piano", false, 1),
            Instrument("Saxophone", false, 65))
    val listOfInstruementArpeges = listOf<Instrument>(Instrument("Trumpet", false, 57), Instrument("Piano", false, 1),
            Instrument("Saxophone", false, 65))
    val listOfInstruement = listOf<Instrument>(Instrument("Enabled drums", false,0x41))
    var  mediaPlayer = MediaPlayer()
    var index = 0
    var lastindex = 0
    var serverSocket = SocketServer(this, "163.172.128.43")
    var thread = Thread(serverSocket)
    var handler = Handler()
    lateinit var runnable: Runnable
    private lateinit var textViewTotalDuration :TextView

    companion object {
        val MUSIQUEPARAM: Int = 0x1
        val STYLE: Int = 0x11
        val JAZZ: Int = 0x111
        val BLUES: Int = 0x211
        val ADDCHORD: Int = 0x21
        val REMOVECHORD: Int = 0x61
        val ADDARPEGE: Int = 0x31
        val REMOVEARPEGE: Int = 0x71
        val DRUM: Int = 0x41
        val DRUMTRUE: Int = 0x141
        val DRUMFALSE: Int = 0x241
        val BMP:Int = 0x51
        val PLAYERCTRL: Int = 0x2
        val PLAY: Int = 0x12
        val PAUSE: Int = 0x32

    }




    fun manageFluxAudio(message : String){

    }

    override fun failedBindSocket(message: String?) {

    }
    override fun getListenerSocket(buffer: ByteArray){
        var codeStatus = 0
        if (buffer.size > 4){
            for (i in 0..3){
                codeStatus +=(buffer.get(i).toInt() and 0xFF)
            }
        }
        println("code recieve = " + codeStatus)
        print("messssage : ")
        for (i in 1..buffer.size){
            print(buffer.get(i-1).toChar())
        }
        println()
        if (buffer.size > 4){

        }

        if (buffer.size > 4 && codeStatus == 0x4){
            var message = buffer.copyOfRange(4, buffer.size)
            try {

                    var path = Environment.getExternalStorageDirectory().toString();
                    var directory = File(path  + "/bardeMusique");
                    directory.mkdir()
                    var file = File(directory, "bbbbarde.mid")
                    var modeAppend = false
                    if (file.exists()){
                        if (!AudioBardeManager.firstPlay && !AudioBardeManager.startingPreparing){
                            file.delete()
                            modeAppend = false
                        }else{
                            modeAppend = true
                        }
                    }
                    var fos  = FileOutputStream(file, modeAppend)
                    fos.write(message)
                    fos.close()

                    if (!AudioBardeManager.firstPlay && !AudioBardeManager.startingPreparing){
                        AudioBardeManager.firstPlay = true
                        AudioBardeManager.mediaPlayer = MediaPlayer()
                        println("on reset player")
                        var fis = FileInputStream(file)
                        var fd = fis.getFD()
                        AudioBardeManager.startingPreparing = true;

                        AudioBardeManager.mediaPlayer.setDataSource(fd)
                        fis.close()

                        AudioBardeManager.mediaPlayer.setOnPreparedListener(this);
                        AudioBardeManager.mediaPlayer.prepareAsync()
                        //mediaPlayer.start()
                    }



            }catch (e : Exception){
                println("error = "+ e.message)
            }

        }else if (buffer.size > 4 && codeStatus == 0xC8){
            /*if (mediaPlayer.isPlaying){
                mediaPlayer.stop()
                AudioBardeManager.firstPlay = true
                AudioBardeManager.startingPreparing = false
                serverSocket.sendToServer(intArrayOf(0x2, 0x42))

            }*/
            println("le message recu est positive")
        }
    }

    override fun onPrepared(p0: MediaPlayer) {
        button_generation.setImageResource(R.drawable.ic_pause_circle_filled_white_48dp)
        AudioBardeManager.mediaPlayer.start()
        playerCtrl()
        button_generation.isEnabled = true
    }

    fun playerCtrl(){
        println(" caeoceifnaeiofnaeiofnzeiofnzeio--------------")
        try {
            total_duration?.text = String.format("%02d:%02d",
                    TimeUnit.MILLISECONDS.toMinutes(AudioBardeManager.mediaPlayer.duration.toLong()),
                    TimeUnit.MILLISECONDS.toSeconds(AudioBardeManager.mediaPlayer.duration.toLong()) -
                            TimeUnit.MINUTES.toSeconds(TimeUnit.MILLISECONDS.toMinutes(AudioBardeManager.mediaPlayer.duration.toLong()))
            )
            current_position?.text = String.format("%02d:%02d",
                    TimeUnit.MILLISECONDS.toMinutes(AudioBardeManager.mediaPlayer.currentPosition.toLong()),
                    TimeUnit.MILLISECONDS.toSeconds(AudioBardeManager.mediaPlayer.currentPosition.toLong()) -
                            TimeUnit.MINUTES.toSeconds(TimeUnit.MILLISECONDS.toMinutes(AudioBardeManager.mediaPlayer.currentPosition.toLong()))
            )
            seek_bar_duration?.max = AudioBardeManager.mediaPlayer.duration
            seek_bar_duration?.setProgress(AudioBardeManager.mediaPlayer.currentPosition)
            println("la duration total est de = " + AudioBardeManager.mediaPlayer.duration)
            if (AudioBardeManager.mediaPlayer.isPlaying){
                //serverSocket.sendToServer(intArrayOf(PLAYERCTRL, PLAY))
                runnable = Runnable {
                    playerCtrl()
                }
                handler.postDelayed(runnable, 1000)

            }
        }catch (e : Exception){
            e.printStackTrace()
        }


    }
    override fun onCreateView(inflater: LayoutInflater?, container: ViewGroup?, savedInstanceState: Bundle?): View?  {
        println("coucoucoucoucoucoucou----------------------------")
        return inflater!!.inflate(R.layout.fragment_generation, container, false)
    }
    override fun onViewCreated(view: View?, savedInstanceState: Bundle?) {
        textViewTotalDuration = view!!.findViewById<TextView>(R.id.total_duration)
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

        viewSelectButtonGeneration(listOfInstruementChords, R.id.list_instrument_generation_chords, "CHORDS", ADDCHORD, REMOVECHORD)
        viewSelectButtonGeneration(listOfInstruementArpeges, R.id.list_instrument_generation_arpeges, "ARPEGES", ADDARPEGE, REMOVEARPEGE)
        viewSelectButtonGeneration(listOfInstruement, R.id.list_instrument_generation, "BPM", DRUMTRUE, DRUMFALSE)

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

                serverSocket.sendToServer(intArrayOf(MUSIQUEPARAM, BMP, p.toInt()))
                value_bpm.text = (p.toInt().toString() + " BPM")
            }
        })

        seek_bar_duration.setOnSeekBarChangeListener(object : SeekBar.OnSeekBarChangeListener {
            override fun onStartTrackingTouch(p0: SeekBar?) {
            }

            override fun onStopTrackingTouch(p0: SeekBar?) {
            }

            override fun onProgressChanged(seekBar: SeekBar, progress: Int, fromUser: Boolean) {
                if (fromUser){
                    AudioBardeManager.mediaPlayer.seekTo(progress)

                }
            }
        })
        try {
            if (AudioBardeManager.mediaPlayer.isPlaying){
                button_generation.setImageResource(R.drawable.ic_pause_circle_filled_white_48dp)
            }else{
                button_generation.setImageResource(R.drawable.ic_play_circle_filled_white_white_48dp)
            }
        }catch (e : Exception){

        }

        connexionNewServer.setOnClickListener {
            serverSocket.close()
            serverSocket = SocketServer(this, newIp.text.toString())
            if (thread.state != Thread.State.TERMINATED){
                thread.interrupt()
            }
            thread = Thread(serverSocket)
            thread.start()
        }


        button_generation.setOnClickListener {
            if (ContextCompat.checkSelfPermission(context,
                            Manifest.permission.WRITE_EXTERNAL_STORAGE)
                    != PackageManager.PERMISSION_GRANTED) {
                Toast.makeText(context, "before playing music please accept permission from barde setings", Toast.LENGTH_SHORT).show()

            }else if(ContextCompat.checkSelfPermission(context,
                            Manifest.permission.READ_EXTERNAL_STORAGE)
                    != PackageManager.PERMISSION_GRANTED) {
                Toast.makeText(context, "before playing music please accept permission from barde setings", Toast.LENGTH_SHORT).show()



            }else {
                if (AudioBardeManager.firstPlay) {
                    //AudioBardeManager.firstPlay = false
                    println("le premier play bouttton")
                    if (AudioBardeManager.mediaPlayer.isPlaying) {
                        println("c'est en train de play")
                        serverSocket.sendToServer(intArrayOf(PLAYERCTRL, PAUSE))
                        button_generation.setImageResource(R.drawable.ic_play_circle_filled_white_white_48dp)
                        AudioBardeManager.mediaPlayer.pause()
                        handler.removeCallbacks(runnable)

                        //AudioBardeManager.startingPreparing = false
                    } else {
                        button_generation.setImageResource(R.drawable.ic_pause_circle_filled_white_48dp)
                        AudioBardeManager.mediaPlayer.start()
                        handler.postDelayed(runnable, 1000)

                        println("ce n'est pas entrein de play")
                    }
                } else {
                    if (!AudioBardeManager.startingPreparing && !AudioBardeManager.firstPlay) {
                        serverSocket.sendToServer(intArrayOf(PLAYERCTRL, PLAY))
                    }
                }


            }
        }

        seek_bar_bpm.setProgress(0)

    }

    fun viewSelectButtonGeneration(list: List<Instrument>, id : Int, type: String, codeAdd : Int, codeRm: Int){
        var ln = view?.findViewById<LinearLayout>(id)
        val margin = TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_PX, 10.toFloat(), getResources().getDisplayMetrics()).toInt()

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
                println("le code est = " + MUSIQUEPARAM + " "  + instrument.code + " " + codeRm)
                if (instrument.isSelected){
                    if (instrument.code == DRUM){
                        serverSocket.sendToServer(intArrayOf(MUSIQUEPARAM, instrument.code, codeRm))
                    }else{
                        serverSocket.sendToServer(intArrayOf(MUSIQUEPARAM, codeRm, instrument.code))
                    }
                    instrument.isSelected = false
                    button.setBackgroundResource(R.drawable.button_selection_generation)
                    button.setTextColor(Color.WHITE)
                }else{
                    if (instrument.code == DRUM){
                        serverSocket.sendToServer(intArrayOf(MUSIQUEPARAM, instrument.code, codeAdd))
                    }else{
                        serverSocket.sendToServer(intArrayOf(MUSIQUEPARAM, codeAdd, instrument.code))
                    }
                    instrument.isSelected = true
                    button.setBackgroundResource(R.drawable.button_selection_generation_selected)
                    button.setTextColor(Color.parseColor("#CA5E85"))
                }
                /* to remove */
                //println("isplayer = " + mediaPlayer?.isPlaying)

                AudioBardeManager.firstPlay = false
                AudioBardeManager.startingPreparing = false
                try {
                    if (AudioBardeManager.mediaPlayer?.isPlaying){
                        println("je revoic our playeing")
                        handler.removeCallbacks(runnable)
                        button_generation.setImageResource(R.drawable.ic_play_circle_filled_white_white_48dp)
                        serverSocket.sendToServer(intArrayOf(PLAYERCTRL, PLAY))

                    }else{
                        total_duration?.text = "00:00"
                        current_position.text = "00:00"
                        seek_bar_duration.max = 0
                        seek_bar_duration.setProgress(0)
                    }
                    AudioBardeManager.mediaPlayer.release()
                }catch (e : Exception){
                    e.printStackTrace()
                }


                /* -------- */
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
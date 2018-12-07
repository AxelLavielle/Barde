package com.project.barde.barde.ui.fragments

import android.Manifest
import android.content.Intent
import android.content.pm.PackageManager
import android.graphics.Color
import android.media.MediaPlayer
import android.os.Bundle
import android.os.Handler
import android.provider.Settings
import android.support.v4.app.ActivityCompat
import android.support.v4.app.Fragment
import android.support.v4.content.ContextCompat
import android.support.v7.app.AlertDialog
import android.support.v7.widget.LinearLayoutManager
import android.support.v7.widget.OrientationHelper
import android.support.v7.widget.PagerSnapHelper
import android.support.v7.widget.RecyclerView
import android.transition.Slide
import android.util.Log
import android.util.TypedValue
import android.view.Gravity
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.*
import com.project.barde.barde.R
import com.project.barde.barde.TutorialActivity
import com.project.barde.barde.adapter.GenerationAdapter
import com.project.barde.barde.adapter.PlaylistChoiceAdapter
import com.project.barde.barde.static.AudioBardeManager
import com.project.barde.barde.static.ListenerSocket
import com.project.barde.barde.static.PlayerManager
import com.project.barde.barde.static.SocketServer
import com.project.barde.barde.ui.view.ChoiceModel
import com.project.barde.barde.ui.view.RadioModel
import com.project.barde.barde.ui.view.SlideModel
import kotlinx.android.synthetic.main.fragment_generation.*
import java.nio.ByteBuffer
import java.util.concurrent.TimeUnit


/**
 * Created by michael on 17/02/2018.
 */
class GenerationFragment : Fragment(), MediaPlayer.OnPreparedListener, ListenerSocket {


    data class Instrument(val name: String, var isSelected: Boolean, var code: Int, var drum: Boolean) {
        lateinit var _button: Button
        fun setButton(button: Button) {
            _button = button
        }

        fun getButton(): Button {
            return _button
        }
    }

    data class Style(val name: String, var isSelected: Boolean, var code: IntArray, val type: Int) {
        var _button: Button? = null
        fun setButton(button: Button) {
            _button = button
        }

        fun getButton(): Button {
            return this!!._button!!
        }
    }

    lateinit var listOfInstruementChords: List<Instrument>
    lateinit var listOfInstruementArpeges: List<Instrument>
    lateinit var listOfInstruement: List<Instrument>
    var index = 0
    var lastindex = 0
    var handler = Handler()
    lateinit var runnable: Runnable
    var serverIsConnected = false
    private lateinit var textViewTotalDuration: TextView
    var max = 200.0f
    var min = 70.0f
    var m: Float = (max - min) / 100.0f
    var p = 0.0f
    private lateinit var toast: Toast
    lateinit var playerManager: PlayerManager
    lateinit var instrumentList: List<Any>
    lateinit var styleList: List<Style>


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
        val BMP: Int = 0x51
        val PLAYERCTRL: Int = 0x2
        val PLAY: Int = 0x12
        val PAUSE: Int = 0x32

    }

    override fun isConnected(boolean: Boolean) {
        try {
            activity.runOnUiThread {
                AudioBardeManager.serverIsConnected = boolean
                if (AudioBardeManager.serverIsConnected) {
                    listOfInstruementChords = listOf<Instrument>(Instrument(getString(R.string.str_trumpet), false, 57, false), Instrument(getString(R.string.str_piano), false, 1, false),
                            Instrument(getString(R.string.str_saxophone), false, 65, false))
                    listOfInstruementArpeges = listOf<Instrument>(Instrument(getString(R.string.str_trumpet), false, 57, false), Instrument(getString(R.string.str_piano), false, 1, false),
                            Instrument(getString(R.string.str_saxophone), false, 65, false))
                    listOfInstruement = listOf<Instrument>(Instrument(getString(R.string.str_enable_drum), false, DRUM, true))
                    styleList = listOf(
                            Style(getString(R.string.str_jazz), true, intArrayOf(MUSIQUEPARAM, STYLE, JAZZ), JAZZ),
                            Style(getString(R.string.str_blues), false, intArrayOf(MUSIQUEPARAM, STYLE, BLUES), BLUES)
                    )
                    viewSelectButtonGeneration(listOfInstruementChords, R.id.list_instrument_generation_chords, "CHORDS", ADDCHORD, REMOVECHORD)
                    viewSelectButtonGeneration(listOfInstruementArpeges, R.id.list_instrument_generation_arpeges, "ARPEGES", ADDARPEGE, REMOVEARPEGE)
                    viewSelectButtonGeneration(listOfInstruement, R.id.list_instrument_generation, "BPM", DRUMTRUE, DRUMFALSE)
                    loadingServer.setVisibility(View.GONE)
                    geneartionView.setVisibility(View.VISIBLE)
                    AudioBardeManager.serverSocket.sendToServer(intArrayOf(MUSIQUEPARAM, STYLE, JAZZ))
                    instrumentList = listOf(
                            RadioModel(
                                    getString(R.string.str_style),
                                    styleList),
                            ChoiceModel(
                                    getString(R.string.str_chords),
                                    getString(R.string.str_choose_your_instrument),
                                    listOfInstruementChords,
                                    ADDCHORD,
                                    REMOVECHORD,
                                    "CHORDS"),
                            ChoiceModel(
                                    getString(R.string.str_arpege),
                                    getString(R.string.str_choose_your_instrument),
                                    listOfInstruementArpeges,
                                    ADDARPEGE,
                                    REMOVEARPEGE,
                                    "ARPEGES"),
                            ChoiceModel(getString(R.string.str_enable_drum), "", listOfInstruement, DRUMTRUE, DRUMFALSE, "BPM"),
                            SlideModel(getString(R.string.str_choose_your_tempo), 70f, 200f, "BPM", 70)
                    )

                    val layoutManager = LinearLayoutManager(context, OrientationHelper.HORIZONTAL, false)
                    framgment_generation_recyclerview.layoutManager = layoutManager
                    framgment_generation_recyclerview.adapter = GenerationAdapter(instrumentList)
                    val snapHelper = PagerSnapHelper()
                    framgment_generation_recyclerview.onFlingListener = null
                    snapHelper.attachToRecyclerView(framgment_generation_recyclerview)

                    generationPagination = listOf<ImageView?>(

                            view?.findViewById(R.id.pagination_a),
                            view?.findViewById(R.id.pagination_b),
                            view?.findViewById(R.id.pagination_c),
                            view?.findViewById(R.id.pagination_d),
                            view?.findViewById(R.id.pagination_e)
                    )



                    for (pag in generationPagination) {
                        pag?.setImageDrawable(ContextCompat.getDrawable(
                                context,
                                R.drawable.circle_full_white
                        ))
                    }

                    changeDrawable(0,
                            R.drawable.circle_full_pink
                    )

                    oldPageNumber = 0

                    framgment_generation_recyclerview.addOnScrollListener(object : RecyclerView.OnScrollListener() {
                        override fun onScrollStateChanged(recyclerView: RecyclerView?, newState: Int) {
                            super.onScrollStateChanged(recyclerView, newState)
                            if (newState == RecyclerView.SCROLL_STATE_IDLE) {
                                val position = layoutManager.findFirstVisibleItemPosition()
                                Log.i("bug", "posiion =" + layoutManager.findFirstVisibleItemPosition())
                                if (oldPageNumber != position && position >= 0) {
                                    changeDrawable(position,
                                            R.drawable.circle_full_pink
                                    )
                                    changeDrawable(oldPageNumber,
                                            R.drawable.circle_full_white
                                    )
                                    oldPageNumber = position
                                }
                            }

                        }
                    })

                } else {
                    try {
                        button_generation.setImageResource(R.drawable.ic_play_circle_filled_white_white_48dp)
                        total_duration?.text = "00:00"
                        current_position.text = "00:00"
                        seek_bar_duration.max = 0
                        seek_bar_duration.setProgress(0)
                        loadingServer.setVisibility(View.GONE)
                        geneartionView.visibility = View.GONE
                        try_again_button.setVisibility(View.VISIBLE)
                        AudioBardeManager.reset()
                        AudioBardeManager.init()
                        handler.removeCallbacks(runnable)

                    } catch (e: Exception) {

                    }

                }
            }

        } catch (e: Exception) {
            e.printStackTrace()
        }

    }

    override fun failedBindSocket(message: String?) {

    }

    fun showToast(msg: String) {
        /* try{
             toast.cancel()
         }catch (e : UninitializedPropertyAccessException){
             e.printStackTrace()
         }
         toast = Toast.makeText(context, msg, Toast.LENGTH_SHORT)
         toast.show()*/
    }

    override fun getListenerSocket(buffer: ByteArray) {
        var codeStatus = 0
        var typeRequest = 0
        var nbInstrument = 0
        var msg = ""
        var mult = 1
        var byteArray = ByteArray(4)
        var j = 3

        if (buffer.size > 4) {
            for (i in 0..3) {
                byteArray.set(i, buffer.get(j))
                j--
                //codeStatus +=((buffer.get(i).toInt() and 0xFF) * mult)
                //mult *= 10
            }
            codeStatus = ByteBuffer.wrap(byteArray).int
        }
        if (buffer.size > 8 && codeStatus == 0xC8) {
            mult = 1
            j = 3
            for (i in 4..7) {
                byteArray.set(i - 4, buffer.get(j + 4))
                j--
                //typeRequest += ((buffer.get(i).toInt() and 0xFF) * mult)
            }
            typeRequest = ByteBuffer.wrap(byteArray).int
        }
        if (buffer.size > 12 && codeStatus == 0xC8) {
            mult = 1
            j = 3

            for (i in 8..11) {
                byteArray.set(i - 8, buffer.get(j + 8))
                j--
                //nbInstrument += ((buffer.get(i).toInt() and 0xFF) * mult)
            }
            nbInstrument = ByteBuffer.wrap(byteArray).int
            msg = ""
            for (i in 12..(buffer.size - 1)) {
                msg += buffer.get(i).toChar()
            }
        }
        println("code recieve = " + codeStatus)
        println("typeRequest = " + typeRequest)
        println("nbInstrument = " + nbInstrument)
        println("messssage : " + msg)

        for (i in 1..buffer.size) {
            print(buffer.get(i - 1).toChar())
        }
        println()
        if (buffer.size > 4) {

        }

        if (buffer.size > 4 && codeStatus == 0x4) {
            var message = buffer.copyOfRange(4, buffer.size)
            var file = AudioBardeManager.createNewMidiFile(message)
            if (!AudioBardeManager.firstPlay && !AudioBardeManager.startingPreparing) {
                AudioBardeManager.firstPlay = true
                AudioBardeManager.startingPreparing = true
                playerManager = PlayerManager(file, this)

            } else {
                playerManager.addNewTrack(file, AudioBardeManager.indexFile)

            }
            AudioBardeManager.indexFile++

        } else if (buffer.size > 12 && codeStatus == 0xC8) {
            try {
                activity.runOnUiThread {
                    var pass = false
                    when (typeRequest) {
                        ADDCHORD -> {
                            for (chord in listOfInstruementChords) {
                                if (chord.code == nbInstrument) {
                                    chord.isSelected = true
                                    chord._button.setBackgroundResource(R.drawable.button_selection_generation_selected)
                                    chord._button.setTextColor(Color.parseColor("#CA5E85"))
                                    showToast(msg)
                                    pass = true
                                    break
                                }
                            }
                        }
                        ADDARPEGE -> {
                            for (arpege in listOfInstruementArpeges) {
                                if (arpege.code == nbInstrument) {
                                    arpege.isSelected = true
                                    arpege._button.setBackgroundResource(R.drawable.button_selection_generation_selected)
                                    arpege._button.setTextColor(Color.parseColor("#CA5E85"))
                                    showToast(msg)
                                    pass = true

                                    break
                                }
                            }

                        }
                        REMOVEARPEGE -> {
                            for (arpege in listOfInstruementArpeges) {
                                if (arpege.code == nbInstrument) {
                                    arpege.isSelected = false
                                    arpege._button.setBackgroundResource(R.drawable.button_selection_generation)
                                    arpege._button.setTextColor(Color.WHITE)
                                    showToast(msg)
                                    pass = true

                                    break
                                }
                            }

                        }
                        REMOVECHORD -> {
                            for (chord in listOfInstruementChords) {
                                if (chord.code == nbInstrument) {
                                    chord.isSelected = false
                                    chord._button.setBackgroundResource(R.drawable.button_selection_generation)
                                    chord._button.setTextColor(Color.WHITE)
                                    showToast(msg)
                                    pass = true

                                    break
                                }
                            }
                        }
                        DRUM -> {
                            for (list in listOfInstruement) {
                                if (list.code == DRUM) {
                                    if (nbInstrument == DRUMTRUE) {
                                        list.isSelected = true
                                        list._button.setBackgroundResource(R.drawable.button_selection_generation_selected)
                                        list._button.setTextColor(Color.parseColor("#CA5E85"))
                                        showToast(msg)
                                        pass = true
                                        break
                                    } else if (nbInstrument == DRUMFALSE) {
                                        list.isSelected = false
                                        list._button.setBackgroundResource(R.drawable.button_selection_generation)
                                        list._button.setTextColor(Color.WHITE)
                                        showToast(msg)
                                        pass = true
                                        break
                                    }
                                }
                            }

                        }
                        BMP -> {
                            showToast(msg)
                            pass = true
                        }
                        STYLE -> {
                            for (style in styleList) {
                                if (nbInstrument == style.type && style._button != null) {
                                    style.getButton().setBackgroundResource(R.drawable.button_selection_generation_selected)
                                    style.getButton().setTextColor(Color.parseColor("#CA5E85"))
                                    style.isSelected = true
                                } else if (style._button != null) {
                                    style.getButton().setBackgroundResource(R.drawable.button_selection_generation)
                                    style.isSelected = false
                                    style.getButton().setTextColor(Color.WHITE)
                                }
                                pass = true
                            }

                        }
                        else -> {
                            println("-------------------------------------------------------")

                        }
                    }
                    if (AudioBardeManager.firstPlay && pass) {
                        AudioBardeManager.firstPlay = false
                        AudioBardeManager.startingPreparing = false
                        AudioBardeManager.indexFile = 0
                        AudioBardeManager.init()
                        if (playerManager._mediaPlayer.isPlaying) {
                            println("je revoic our playeing")
                            handler.removeCallbacks(runnable)
                            button_generation.setImageResource(R.drawable.ic_play_circle_filled_white_white_48dp)
                            playerManager._mediaPlayer.release()
                            AudioBardeManager.serverSocket.sendToServer(intArrayOf(PLAYERCTRL, PLAY))

                        } else {
                            total_duration?.text = "00:00"
                            current_position.text = "00:00"
                            seek_bar_duration.max = 0
                            seek_bar_duration.setProgress(0)
                            playerManager._mediaPlayer.release()

                        }
                    }
                }

            } catch (e: Exception) {
                e.printStackTrace()
            }
        }

    }

    var t: Long = 0

    override fun onPrepared(p0: MediaPlayer) {
        loadingGeneration.visibility = View.GONE
        button_generation.visibility = View.VISIBLE
        button_generation.setImageResource(R.drawable.ic_pause_circle_filled_white_48dp)
        try {
            handler.removeCallbacks(runnable)

        } catch (e: Exception) {

        }
        playerManager.lengthTrack = p0.duration
        p0.seekTo(playerManager.seekTo)
        p0.start()
        AudioBardeManager.mediaPlayer = p0

        playerCtrl(p0, playerManager.getTotalLength().toLong() - p0.duration.toLong(), -1)
        button_generation.isEnabled = true


    }

    fun playerCtrl(mediaPlayer: MediaPlayer, old: Long, lastCurrentValue: Int) {
        try {
            var t = playerManager.getTotalLength().toLong()
            println("size = " + t)
            total_duration?.text = String.format("%02d:%02d",
                    TimeUnit.MILLISECONDS.toMinutes(t),
                    TimeUnit.MILLISECONDS.toSeconds(t) -
                            TimeUnit.MINUTES.toSeconds(TimeUnit.MILLISECONDS.toMinutes(t))
            )
            var currentPos = mediaPlayer.currentPosition + playerManager.addToCurrentPos()

            current_position?.text = String.format("%02d:%02d",
                    TimeUnit.MILLISECONDS.toMinutes(currentPos.toLong()),
                    TimeUnit.MILLISECONDS.toSeconds(currentPos.toLong()) -
                            TimeUnit.MINUTES.toSeconds(TimeUnit.MILLISECONDS.toMinutes(currentPos.toLong())))
            seek_bar_duration?.max = t.toInt()
            seek_bar_duration?.progress = currentPos
            if (playerManager.isLastIndex()) {
                AudioBardeManager.serverSocket.sendToServer(intArrayOf(PLAYERCTRL, PLAY))

            }
            if (currentPos != lastCurrentValue) {
                runnable = Runnable {
                    playerCtrl(mediaPlayer, old, currentPos)
                }
                handler.postDelayed(runnable, 100)
            } else {
            }


        } catch (e: Exception) {
            e.printStackTrace()
        }


    }

    override fun onCreateView(inflater: LayoutInflater?, container: ViewGroup?, savedInstanceState: Bundle?): View? {

        return inflater!!.inflate(R.layout.fragment_generation, container, false)
    }

    private fun setConnectionToServer(): Boolean {
        if (!AudioBardeManager.serverIsConnected) {
            listOfInstruementChords = listOf<Instrument>(Instrument(getString(R.string.str_trumpet), false, 57, false), Instrument(getString(R.string.str_piano), false, 1, false),
                    Instrument(getString(R.string.str_saxophone), false, 65, false))
            listOfInstruementArpeges = listOf<Instrument>(Instrument(getString(R.string.str_trumpet), false, 57, false), Instrument(getString(R.string.str_piano), false, 1, false),
                    Instrument(getString(R.string.str_saxophone), false, 65, false))
            listOfInstruement = listOf<Instrument>(Instrument(getString(R.string.str_enable_drum), false, DRUM, true))
            loadingServer.setVisibility(View.VISIBLE);
            geneartionView.setVisibility(View.GONE)
            AudioBardeManager.serverSocket = SocketServer(this, getString(R.string.serverIp), getString(R.string.serverPort).toInt())
            AudioBardeManager.thread = Thread(AudioBardeManager.serverSocket)
            AudioBardeManager.thread.start()
            styleList = listOf(
                    Style(getString(R.string.str_jazz), true, intArrayOf(MUSIQUEPARAM, STYLE, JAZZ), JAZZ),
                    Style(getString(R.string.str_blues), false, intArrayOf(MUSIQUEPARAM, STYLE, BLUES), BLUES)
            )


            return true
        } else {
            loadingServer.setVisibility(View.GONE);
            return false
        }
    }

    override fun onViewCreated(view: View?, savedInstanceState: Bundle?) {
        println("coucou je suis la")
        setConnectionToServer()
        try_again_button.setOnClickListener {
            try_again_button.visibility = View.GONE
            setConnectionToServer()
        }

        textViewTotalDuration = view!!.findViewById<TextView>(R.id.total_duration)
        var listOfChoice = listOf<LinearLayout>(style_choice_genearation, instrument_choice_generation_chords,
                instrument_choice_generation_arpeges, instrument_choice_generation, rythme_choice_genaration)
        var listOfPanination = listOf<ImageView>(pagination_a, pagination_b, pagination_c, pagination_d, pagination_e)

        /*add_to_playlist.setOnClickListener {
            add_to_playlist()

        }*/
        /*if (AudioBardeManager.thread.state == Thread.State.NEW){
            AudioBardeManager.thread.start()
        }*/
        for (choice in listOfChoice) {
            choice.visibility = View.GONE
        }

        next_button_generation.visibility = View.VISIBLE
        previous_button_generation.visibility = View.VISIBLE
        try {
            viewSelectButtonGeneration(listOfInstruementChords, R.id.list_instrument_generation_chords, "CHORDS", ADDCHORD, REMOVECHORD)
            viewSelectButtonGeneration(listOfInstruementArpeges, R.id.list_instrument_generation_arpeges, "ARPEGES", ADDARPEGE, REMOVEARPEGE)
            viewSelectButtonGeneration(listOfInstruement, R.id.list_instrument_generation, "BPM", DRUMTRUE, DRUMFALSE)

            instrumentList = listOf(
                    RadioModel(
                            getString(R.string.str_style),
                            styleList),
                    ChoiceModel(
                            getString(R.string.str_chords),
                            getString(R.string.str_choose_your_instrument),
                            listOfInstruementChords,
                            ADDCHORD,
                            REMOVECHORD,
                            "CHORDS"),
                    ChoiceModel(
                            getString(R.string.str_arpege),
                            getString(R.string.str_choose_your_instrument),
                            listOfInstruementArpeges,
                            ADDARPEGE,
                            REMOVEARPEGE,
                            "ARPEGES"),
                    ChoiceModel(getString(R.string.str_enable_drum), "", listOfInstruement, DRUMTRUE, DRUMFALSE, "BPM"),
                    SlideModel(getString(R.string.str_choose_your_tempo), 70f, 200f, "BPM", 70)
            )

            val layoutManager = LinearLayoutManager(context, OrientationHelper.HORIZONTAL, false)
            framgment_generation_recyclerview.layoutManager = layoutManager
            framgment_generation_recyclerview.adapter = GenerationAdapter(instrumentList)
            val snapHelper = PagerSnapHelper()
            framgment_generation_recyclerview.onFlingListener = null
            snapHelper.attachToRecyclerView(framgment_generation_recyclerview)

            generationPagination = listOf<ImageView?>(

                    view?.findViewById(R.id.pagination_a),
                    view?.findViewById(R.id.pagination_b),
                    view?.findViewById(R.id.pagination_c),
                    view?.findViewById(R.id.pagination_d),
                    view?.findViewById(R.id.pagination_e)
            )



            for (pag in generationPagination) {
                pag?.setImageDrawable(ContextCompat.getDrawable(
                        context,
                        R.drawable.circle_full_white
                ))
            }

            changeDrawable(0,
                    R.drawable.circle_full_pink
            )

            oldPageNumber = 0

            framgment_generation_recyclerview.addOnScrollListener(object : RecyclerView.OnScrollListener() {
                override fun onScrollStateChanged(recyclerView: RecyclerView?, newState: Int) {
                    super.onScrollStateChanged(recyclerView, newState)
                    if (newState == RecyclerView.SCROLL_STATE_IDLE) {
                        val position = layoutManager.findFirstVisibleItemPosition()
                        Log.i("bug", "posiion =" + layoutManager.findFirstVisibleItemPosition())
                        if (oldPageNumber != position && position >= 0) {
                            changeDrawable(position,
                                    R.drawable.circle_full_pink
                            )
                            changeDrawable(oldPageNumber,
                                    R.drawable.circle_full_white
                            )
                            oldPageNumber = position
                        }
                    }

                }
            })
        } catch (e: Exception) {
            e.printStackTrace()
        }


        if (index == 0) {
            listOfPanination.get(0).setImageResource(R.drawable.circle_full_pink)
            listOfChoice.get(0).visibility = View.VISIBLE
            previous_button_generation.visibility = View.INVISIBLE
        } else {
            listOfPanination.get(index).setImageResource(R.drawable.circle_full_pink)
            listOfChoice.get(index).visibility = View.VISIBLE
            if (index >= listOfChoice.size - 1) {
                next_button_generation.visibility = View.INVISIBLE
            }
        }


        next_button_generation.setOnClickListener {
            if (index < (listOfChoice.size - 1)) {
                lastindex = index
                index++
                listOfPanination.get(lastindex).setImageResource(R.drawable.circle_full_white)
                listOfPanination.get(index).setImageResource(R.drawable.circle_full_pink)
                listOfChoice.get(lastindex).visibility = View.GONE
                listOfChoice.get(index).visibility = View.VISIBLE
                previous_button_generation.visibility = View.VISIBLE
                if (index >= (listOfChoice.size - 1)) {
                    next_button_generation.visibility = View.INVISIBLE
                }
            }
        }

        previous_button_generation.setOnClickListener {
            if (index > 0) {
                lastindex = index
                index--
                listOfPanination.get(lastindex).setImageResource(R.drawable.circle_full_white)
                listOfPanination.get(index).setImageResource(R.drawable.circle_full_pink)
                listOfChoice.get(lastindex).visibility = View.GONE
                listOfChoice.get(index).visibility = View.VISIBLE
                next_button_generation.visibility = View.VISIBLE
                if (index <= 0) {
                    previous_button_generation.visibility = View.INVISIBLE
                }
            }
        }


        jazz_style_radio.setOnClickListener {
            if (jazz_style_radio.isChecked) {
                AudioBardeManager.serverSocket.sendToServer(intArrayOf(MUSIQUEPARAM, STYLE, JAZZ))
            }
        }
        blues_style_radio.setOnClickListener {
            if (blues_style_radio.isChecked) {
                AudioBardeManager.serverSocket.sendToServer(intArrayOf(MUSIQUEPARAM, STYLE, BLUES))

            }
        }
        style_button_radio.setOnCheckedChangeListener { radioGroup, i ->
            println("event click radio ----------------------------")

            /*jazz_style_radio.setBackgroundResource(R.drawable.button_selection_generation)
            jazz_style_radio.setTextColor(Color.WHITE)
            blues_style_radio.setBackgroundResource(R.drawable.button_selection_generation)
            blues_style_radio.setTextColor(Color.WHITE)
            if (jazz_style_radio.isChecked){
                //AudioBardeManager.serverSocket.rec().println("MUSIQUEPARAM;STYLE;BLUE")
                jazz_style_radio.setBackgroundResource(R.drawable.button_selection_generation_selected)
                jazz_style_radio.setTextColor(Color.parseColor("#CA5E85"))
            }else if (blues_style_radio.isChecked){
                //AudioBardeManager.serverSocket.rec().println("MUSIQUEPARAM;STYLE;JAZZ")
                blues_style_radio.setBackgroundResource(R.drawable.button_selection_generation_selected)
                blues_style_radio.setTextColor(Color.parseColor("#CA5E85"))

            }*/
        }
        seek_bar_bpm.setOnSeekBarChangeListener(object : SeekBar.OnSeekBarChangeListener {

            override fun onStartTrackingTouch(p0: SeekBar?) {
            }

            override fun onStopTrackingTouch(p0: SeekBar?) {
                AudioBardeManager.serverSocket.sendToServer(intArrayOf(MUSIQUEPARAM, BMP, p.toInt()))
            }

            override fun onProgressChanged(seekBar: SeekBar, progress: Int, fromUser: Boolean) {
                p = (m * progress) + min

                value_bpm.text = (p.toInt().toString() + " BPM")
            }
        })

        seek_bar_duration.setOnSeekBarChangeListener(object : SeekBar.OnSeekBarChangeListener {
            override fun onStartTrackingTouch(p0: SeekBar?) {
            }

            override fun onStopTrackingTouch(p0: SeekBar?) {
            }

            override fun onProgressChanged(seekBar: SeekBar, progress: Int, fromUser: Boolean) {
                try {
                    if (fromUser) {
                        try {
                            handler.removeCallbacks(runnable)
                        } catch (e: Exception) {

                        }
                        playerManager.playAtThisTrackAtThisTime(progress)
                        t = 0
                        //AudioBardeManager.mediaPlayer.seekTo(progress)

                    }
                } catch (e: Exception) {
                    e.printStackTrace()
                }

            }
        })
        try {
            if (AudioBardeManager.mediaPlayer.isPlaying) {
                button_generation.setImageResource(R.drawable.ic_pause_circle_filled_white_48dp)
            } else {
                button_generation.setImageResource(R.drawable.ic_play_circle_filled_white_white_48dp)
            }
        } catch (e: Exception) {

        }

        connexionNewServer.setOnClickListener {
            AudioBardeManager.serverSocket.close()
            AudioBardeManager.serverSocket = SocketServer(this, newIp.text.toString(), 23)
            if (AudioBardeManager.thread.state != Thread.State.TERMINATED) {
                AudioBardeManager.thread.interrupt()
            }
            AudioBardeManager.thread = Thread(AudioBardeManager.serverSocket)
            AudioBardeManager.thread.start()
        }


        button_generation.setOnClickListener {
            if (ContextCompat.checkSelfPermission(context,
                            Manifest.permission.WRITE_EXTERNAL_STORAGE)
                    != PackageManager.PERMISSION_GRANTED) {
                requestPermissions(arrayOf(Manifest.permission.WRITE_EXTERNAL_STORAGE, Manifest.permission.READ_EXTERNAL_STORAGE), 1)


            } else if (ContextCompat.checkSelfPermission(context,
                            Manifest.permission.READ_EXTERNAL_STORAGE)
                    != PackageManager.PERMISSION_GRANTED) {
                requestPermissions(arrayOf(Manifest.permission.READ_CONTACTS, Manifest.permission.READ_EXTERNAL_STORAGE), 1
                )


            } else {
                if (AudioBardeManager.firstPlay) {
                    if (playerManager._mediaPlayer.isPlaying) {
                        button_generation.setImageResource(R.drawable.ic_play_circle_filled_white_white_48dp)
                        playerManager._mediaPlayer.pause()
                        if (runnable != null) {
                            handler.removeCallbacks(runnable)
                        }
                    } else {
                        button_generation.setImageResource(R.drawable.ic_pause_circle_filled_white_48dp)
                        playerManager._mediaPlayer.start()
                        if (runnable != null) {
                            handler.postDelayed(runnable, 1000)
                        }
                    }
                } else {
                    if (!AudioBardeManager.startingPreparing && !AudioBardeManager.firstPlay) {
                        AudioBardeManager.indexFile = 0
                        AudioBardeManager.init()
                        AudioBardeManager.serverSocket.sendToServer(intArrayOf(PLAYERCTRL, PLAY))
                    }
                }


            }
        }

        seek_bar_bpm.setProgress(0)

        help.setOnClickListener {
            TutorialActivity.startActivity(context)
        }



    }
    private fun changeDrawable(position: Int, id: Int) {
        generationPagination[position]
                ?.setImageDrawable(ContextCompat.getDrawable(
                        context,
                        id
                ))
    }

    lateinit var generationPagination: List<ImageView?>
    var oldPageNumber = 0
    override fun onRequestPermissionsResult(requestCode: Int, permissions: Array<out String>, grantResults: IntArray) {
        println("requestCode = " + requestCode)
        println("empty = " + grantResults.isNotEmpty())
        println("requestCode = " + grantResults)
        when (requestCode) {
            1 -> {
                if ((grantResults.isNotEmpty() && grantResults[0] == PackageManager.PERMISSION_GRANTED)) {
                    if (AudioBardeManager.firstPlay) {
                        if (playerManager._mediaPlayer.isPlaying) {
                            button_generation.setImageResource(R.drawable.ic_play_circle_filled_white_white_48dp)
                            playerManager._mediaPlayer.pause()
                            if (runnable != null) {
                                handler.removeCallbacks(runnable)
                            }
                        } else {
                            button_generation.setImageResource(R.drawable.ic_pause_circle_filled_white_48dp)
                            playerManager._mediaPlayer.start()
                            if (runnable != null) {
                                handler.postDelayed(runnable, 1000)
                            }
                        }
                    } else {
                        if (!AudioBardeManager.startingPreparing && !AudioBardeManager.firstPlay) {
                            AudioBardeManager.indexFile = 0
                            AudioBardeManager.init()
                            AudioBardeManager.serverSocket.sendToServer(intArrayOf(PLAYERCTRL, PLAY))
                        }
                    }
                } else {
                }
                return

            }
        }
    }

    fun viewSelectButtonGeneration(list: List<Instrument>, id: Int, type: String, codeAdd: Int, codeRm: Int) {
        var ln = view?.findViewById<LinearLayout>(id)
        ln?.removeAllViews()

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
        for (instrument in list) {
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
                println("le code est = " + MUSIQUEPARAM + " " + instrument.code + " " + codeRm)
                if (instrument.isSelected) {
                    if (instrument.drum) {
                        AudioBardeManager.serverSocket.sendToServer(intArrayOf(MUSIQUEPARAM, instrument.code, codeRm))
                    } else {
                        AudioBardeManager.serverSocket.sendToServer(intArrayOf(MUSIQUEPARAM, codeRm, instrument.code))
                    }

                } else {
                    if (instrument.drum) {
                        AudioBardeManager.serverSocket.sendToServer(intArrayOf(MUSIQUEPARAM, instrument.code, codeAdd))
                    } else {
                        AudioBardeManager.serverSocket.sendToServer(intArrayOf(MUSIQUEPARAM, codeAdd, instrument.code))
                    }

                }
                instrument.setButton(button)

                /* to remove */
                //println("isplayer = " + mediaPlayer?.isPlaying)


                /* -------- */
            }
        }
    }

    fun add_to_playlist() {
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
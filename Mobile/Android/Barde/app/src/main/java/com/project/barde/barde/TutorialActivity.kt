package com.project.barde.barde

import android.content.Context
import android.content.Intent
import android.graphics.drawable.Drawable
import android.media.Image
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.support.v4.content.ContextCompat
import android.support.v7.widget.*
import android.util.Log
import android.view.View
import android.widget.ImageView
import com.project.barde.barde.adapter.TutorialListAdapter
import com.project.barde.barde.model.TutoPage
import kotlinx.android.synthetic.main.activity_tutorial.*
import kotlinx.android.synthetic.main.fragment_generation.*

class TutorialActivity : AppCompatActivity() {
    companion object {
        fun startActivity(actualActivity: Context) {
            val intent = Intent(actualActivity, TutorialActivity::class.java)
            actualActivity.startActivity(intent)
        }
    }


    lateinit var tutorial: List<TutoPage>
    lateinit var tutoPagination: List<ImageView>
    var oldPageNumber = 0
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_tutorial)
        init()

        val recyclerView = findViewById<RecyclerView>(R.id.activity_tutorial_recyckerView)
        val layoutManager = LinearLayoutManager(this, OrientationHelper.HORIZONTAL, false)
        recyclerView.layoutManager = layoutManager
        recyclerView.adapter = TutorialListAdapter(tutorial)
        val snapHelper = PagerSnapHelper()
        snapHelper.attachToRecyclerView(recyclerView)

        activity_tutorial_skip.setOnClickListener {
            onBackPressed()
        }

        changeDrawable(0,
                R.drawable.circle_full_pink
        )
        recyclerView.addOnScrollListener(object : RecyclerView.OnScrollListener() {
            override fun onScrollStateChanged(recyclerView: RecyclerView?, newState: Int) {
                super.onScrollStateChanged(recyclerView, newState)
                if (newState == RecyclerView.SCROLL_STATE_IDLE) {
                    val position = layoutManager.findFirstVisibleItemPosition()
                    Log.i("bug", "posiion =" + layoutManager.findFirstVisibleItemPosition())
                    if (oldPageNumber != position) {
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
        activity_tutorial_overlay.setOnClickListener {
            activity_tutorial_overlay.visibility = View.GONE
            activity_tutorial_image.visibility = View.GONE
        }

        activity_tutorial_image.setOnClickListener {
            activity_tutorial_overlay.visibility = View.GONE
            activity_tutorial_image.visibility = View.GONE
        }
    }

    private fun changeDrawable(position: Int, id: Int) {
        tutoPagination[position]
                .setImageDrawable(ContextCompat.getDrawable(
                this,
                id
        ))
    }

    private fun init() {
        tutorial = listOf(
                TutoPage(
                        getString(R.string.activity_tutorail_page_one_title),
                        getString(R.string.activity_tutorail_page_one_subtitle),
                        ContextCompat.getDrawable(this, R.drawable.barde),
                        getString(R.string.activity_tutorail_page_one_text)),
                TutoPage(
                        getString(R.string.activity_tutorail_page_two_title),
                        getString(R.string.activity_tutorail_page_two_subtitle),
                        ContextCompat.getDrawable(this, R.drawable.barde),
                        getString(R.string.activity_tutorail_page_two_text)),
                TutoPage(
                        getString(R.string.activity_tutorail_page_three_title),
                        getString(R.string.activity_tutorail_page_three_subtitle),
                        ContextCompat.getDrawable(this, R.drawable.barde),
                        getString(R.string.activity_tutorail_page_three_text)),
                TutoPage(
                        getString(R.string.activity_tutorail_page_four_title),
                        getString(R.string.activity_tutorail_page_four_subtitle),
                        ContextCompat.getDrawable(this, R.drawable.barde),
                        getString(R.string.activity_tutorail_page_four_text)),
                TutoPage(
                        getString(R.string.activity_tutorail_page_six_title),
                        getString(R.string.activity_tutorail_page_six_subtitle),
                        ContextCompat.getDrawable(this, R.drawable.barde),
                        getString(R.string.activity_tutorail_page_six_text)),
                TutoPage(
                        getString(R.string.activity_tutorail_page_seven_title),
                        getString(R.string.activity_tutorail_page_seven_subtitle),
                        ContextCompat.getDrawable(this, R.drawable.barde),
                        getString(R.string.activity_tutorail_page_seven_text))
        )
        //init pagination
        findViewById<ImageView>(R.id.tuto_pagination_b)
        tutoPagination = listOf<ImageView>(

                findViewById(R.id.tuto_pagination_a),
                findViewById(R.id.tuto_pagination_b),
                findViewById(R.id.tuto_pagination_c),
                findViewById(R.id.tuto_pagination_d),
                findViewById(R.id.tuto_pagination_e),
                findViewById(R.id.tuto_pagination_f)
        )

    }
}

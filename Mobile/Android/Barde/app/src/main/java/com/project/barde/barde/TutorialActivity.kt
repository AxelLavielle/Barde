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
import com.project.barde.barde.R.id.tutorial_list_item_view_text_lets_go
import com.project.barde.barde.adapter.TutorialListAdapter
import com.project.barde.barde.model.Listener
import com.project.barde.barde.model.TutoPage
import kotlinx.android.synthetic.main.activity_tutorial.*
import kotlinx.android.synthetic.main.fragment_generation.*

class TutorialActivity : AppCompatActivity(), Listener {
    override fun onCLick() {
        onBackPressed()
    }

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
                        R.drawable.barde,
                        getString(R.string.activity_tutorail_page_one_text), this),
                TutoPage(
                        getString(R.string.activity_tutorail_page_two_title),
                        getString(R.string.activity_tutorail_page_two_subtitle),
                        R.drawable.tuto1,
                        getString(R.string.activity_tutorail_page_two_text), this),
                TutoPage(
                        getString(R.string.activity_tutorail_page_three_title),
                        getString(R.string.activity_tutorail_page_three_subtitle),
                        R.drawable.tuto2,
                        getString(R.string.activity_tutorail_page_three_text), this),
                TutoPage(
                        getString(R.string.activity_tutorail_page_four_title),
                        getString(R.string.activity_tutorail_page_four_subtitle),
                        R.drawable.tuto3,
                        getString(R.string.activity_tutorail_page_four_text), this),
                TutoPage(
                        getString(R.string.activity_tutorail_page_six_title),
                        getString(R.string.activity_tutorail_page_six_subtitle),
                        R.drawable.tuto5,
                        getString(R.string.activity_tutorail_page_six_text), this),
                TutoPage(
                        getString(R.string.activity_tutorail_page_seven_title),
                        getString(R.string.activity_tutorail_page_seven_subtitle),
                        R.drawable.tuto4,
                        getString(R.string.activity_tutorail_page_seven_text),
                        this)
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

package com.project.barde.barde.ui.fragments

import android.content.Intent
import android.os.Bundle
import android.support.v4.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.TextView
import com.github.kittinunf.fuel.core.FuelManager
import com.project.barde.barde.R
import com.project.barde.barde.db.UserDbHelper
import com.project.barde.barde.db.UserTable
import com.project.barde.barde.db.database
import com.project.barde.barde.ui.activities.FirstPage
import com.project.barde.barde.ui.activities.UserProfileActivity
import kotlinx.android.synthetic.main.fragment_user_page.*

/**
 * Created by michael on 11/02/2018.
 */
class UserPageFragment : Fragment(), UserDbHelper.dataListener {
    override fun updateUser() {
        activity.database.use {
            val c = rawQuery("SELECT * FROM user LIMIT 1", null)
            if(c.count >= 1){
                c.moveToFirst()
                (view as View).findViewById<TextView>(R.id.activity_main_email).setText(c.getString(c.getColumnIndex(UserTable.EMAIL)))
                (view as View).findViewById<TextView>(R.id.activity_main_full_name).setText(c.getString(c.getColumnIndex(UserTable.FIRSTNAME)) + " " + c.getString(c.getColumnIndex(UserTable.LASTNAME)))
            }
        }
    }

    var view: Any? = null

    override fun onCreateView(inflater: LayoutInflater?, container: ViewGroup?, savedInstanceState: Bundle?): View? {
        view = inflater!!.inflate(R.layout.fragment_user_page, container, false) as View
        activity.database.listener.add(this)
        updateUser()
        (view as View).findViewById<Button>(R.id.user_page_logout).setOnClickListener {
            FuelManager.instance.baseHeaders = mapOf("Authorization" to "")
            startActivity(Intent(activity, FirstPage::class.java))
        }
        (view as View).findViewById<Button>(R.id.update_profile).setOnClickListener {
            startActivity(Intent(activity, UserProfileActivity::class.java))
        }
        return view as View
    }

    fun getUserInfo(){
        activity.database.use {
            val c = rawQuery("SELECT * FROM user LIMIT 1", null)
            if(c.count >= 1){
                c.moveToFirst()
                (view as View).findViewById<TextView>(R.id.activity_main_email).setText(c.getString(c.getColumnIndex(UserTable.EMAIL)))
                (view as View).findViewById<TextView>(R.id.activity_main_full_name).setText(c.getString(c.getColumnIndex(UserTable.FIRSTNAME)) + " " + c.getString(c.getColumnIndex(UserTable.LASTNAME)))
            }
        }
    }
}
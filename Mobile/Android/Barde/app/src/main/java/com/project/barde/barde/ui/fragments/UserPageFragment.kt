package com.project.barde.barde.ui.fragments

import android.app.Dialog
import android.content.Intent
import android.content.res.Resources
import android.os.Bundle
import android.support.v4.app.Fragment
import android.support.v7.app.AlertDialog
import android.text.AlteredCharSequence
import android.view.*
import android.widget.Button
import android.widget.TextView
import com.github.kittinunf.fuel.core.FuelManager
import com.project.barde.barde.R
import com.project.barde.barde.db.UserDbHelper
import com.project.barde.barde.db.UserTable
import com.project.barde.barde.db.database
import com.project.barde.barde.ui.activities.FirstPage
import com.project.barde.barde.ui.activities.SettingsActivity
import com.project.barde.barde.ui.activities.SubscriptionActivity
import com.project.barde.barde.ui.activities.UserProfileActivity
import kotlinx.android.synthetic.main.fragment_user_page.*

/**
 * Created by michael on 11/02/2018.
 */
class UserPageFragment : Fragment(), UserDbHelper.dataListener {
    private lateinit var v : View

    override fun updateUser() {
        activity.database.use {
            val c = rawQuery("SELECT * FROM user LIMIT 1", null)
            if(c.count >= 1){
                c.moveToFirst()
                v.findViewById<TextView>(R.id.activity_main_email).setText(c.getString(c.getColumnIndex(UserTable.EMAIL)))
                v.findViewById<TextView>(R.id.activity_main_full_name).setText(c.getString(c.getColumnIndex(UserTable.FIRSTNAME)) + " " + c.getString(c.getColumnIndex(UserTable.LASTNAME)))
            }
        }
    }

    override fun onCreateView(inflater: LayoutInflater?, container: ViewGroup?, savedInstanceState: Bundle?): View? {
        v = inflater!!.inflate(R.layout.fragment_user_page, container, false) as View
        activity.database.listener.add(this)
        updateUser()
        v.findViewById<Button>(R.id.user_page_logout).setOnClickListener {
            FuelManager.instance.baseHeaders = mapOf("Authorization" to "")
            startActivity(Intent(activity, FirstPage::class.java))
        }
        v.findViewById<Button>(R.id.update_profile).setOnClickListener {
            startActivity(Intent(activity, UserProfileActivity::class.java))
        }
        v.findViewById<Button>(R.id.update_setting).setOnClickListener {
            startActivity(Intent(activity, SettingsActivity::class.java))
        }
        v.findViewById<Button>(R.id.update_subscribe).setOnClickListener {
            subscribeFun()        }
        v.findViewById<Button>(R.id.update_promot_code).setOnClickListener{
           promotCodeFun()
        }
        return v
    }

    fun getUserInfo(){
        activity.database.use {
            val c = rawQuery("SELECT * FROM user LIMIT 1", null)
            if(c.count >= 1){
                c.moveToFirst()
                v.findViewById<TextView>(R.id.activity_main_email).setText(c.getString(c.getColumnIndex(UserTable.EMAIL)))
                v.findViewById<TextView>(R.id.activity_main_full_name).setText(c.getString(c.getColumnIndex(UserTable.FIRSTNAME)) + " " + c.getString(c.getColumnIndex(UserTable.LASTNAME)))
            }
        }
    }

    fun promotCodeFun(){
        val builder = AlertDialog.Builder(activity)
        val inflater = layoutInflater
        val view = inflater.inflate(R.layout.dialog_promot_code, null)
        builder.setView(view)
        val dialog = builder.create()
        dialog.show()
    }

    fun subscribeFun(){

        val builder = AlertDialog.Builder(activity)
        val inflater = layoutInflater
        val view = inflater.inflate(R.layout.dialog_subcription, null)
        builder.setView(view)
        val dialog = builder.create()
        dialog.show()
    }
}
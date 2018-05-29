package com.project.barde.barde.ui.activities

import android.app.DatePickerDialog
import android.graphics.Color
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.text.Editable
import android.text.TextWatcher
import android.view.Gravity
import android.view.View
import android.widget.TextView
import android.widget.Toast
import com.github.kittinunf.fuel.httpPut
import com.github.kittinunf.result.Result
import com.google.gson.Gson
import com.project.barde.barde.R
import com.project.barde.barde.db.UserDbHelper
import com.project.barde.barde.db.UserTable
import com.project.barde.barde.db.database
import com.project.barde.barde.model.Login
import com.project.barde.barde.model.Msg
import kotlinx.android.synthetic.main.activity_profile_user.*

/**
 * Created by michael on 11/11/2017.
 */

class UserProfileActivity : AppCompatActivity(), UserDbHelper.dataListener, TextWatcher {
    private var year = 0
    private var month = 0
    private var dayOfMonth = 0
    private var edit = true
    private lateinit var okButton : TextView
    private lateinit var backButton : TextView
    private lateinit var cancelButton : TextView
    private lateinit var username : String

    override fun beforeTextChanged(p0: CharSequence?, p1: Int, p2: Int, p3: Int) {
    }

    override fun onTextChanged(p0: CharSequence?, p1: Int, p2: Int, p3: Int) {
    }

    override fun afterTextChanged(p0: Editable?) {
        if (!edit){
            profile_user_header_button_start.removeView(backButton)
            profile_user_header_button_start.addView(cancelButton)
            profile_user_header_button_end.addView(okButton)
            edit = true
        }
    }

    override fun updateUser() {
        database.use {
            val c = rawQuery("SELECT * FROM user LIMIT 1", null)
            if(c.count >= 1){
                edit = true
                c.moveToFirst()
                update_email.setText(c.getString(c.getColumnIndex(UserTable.EMAIL)))
                /*update_password.setText(c.getString(c.getColumnIndex(UserTable.PASSWORD)))*/
                update_firstname.setText(c.getString(c.getColumnIndex(UserTable.FIRSTNAME)))
                update_lastname.setText(c.getString(c.getColumnIndex(UserTable.LASTNAME)))
                username = c.getString(c.getColumnIndex(UserTable.USERNAME))
                year = c.getInt(c.getColumnIndex(UserTable.YEAROFBIRTHDAY))
                month = c.getInt(c.getColumnIndex(UserTable.MONTHOFBIRTHDAY))
                dayOfMonth = c.getInt(c.getColumnIndex(UserTable.DAYOFBIRTHDAY))
                update_dateofbirthday.setText(StringBuilder().append(dayOfMonth).append("/")
                        .append(month + 1).append("/").append(year))
                edit = false
            }
        }
    }

    private fun updateData(){
        StringBuilder(getString(R.string.api)).append("/user").toString()
                .httpPut(listOf("email" to update_email.text, /*"password" to update_password.text,*/ "firstName" to update_firstname.text,
                        "lastName" to update_lastname.text, "yearOfBirth" to year,
                        "monthOfBirth" to month, "dayOfBirth" to dayOfMonth, "userName" to username)).responseString { request, response, result ->
            println(String(response.data))
            if (response.statusCode == 200){
                val update: Login = Gson().fromJson(String(response.data), Login::class.java)
                Toast.makeText(this, update.msg, Toast.LENGTH_SHORT).show()
                when (result) {
                    is Result.Success -> {
                        database.updateUser()
                        finish()
                    }
                }
            }else{
                val msg: Msg = Gson().fromJson(String(response.data), Msg::class.java)
                Toast.makeText(this, msg.data.message, Toast.LENGTH_SHORT).show()
            }

        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_profile_user)

        backButton = TextView(this)
        backButton.setText(getString(R.string.str_back))
        backButton.setTextColor(Color.WHITE)
        backButton.setOnClickListener{
            finish()
        }

        cancelButton = TextView(this)
        cancelButton.setText(getString(R.string.str_cancel))
        cancelButton.setTextColor(Color.WHITE)
        cancelButton.setOnClickListener {
            profile_user_header_button_start.removeView(cancelButton)
            profile_user_header_button_start.addView(backButton)
            profile_user_header_button_end.removeView(okButton)
            updateUser()
            edit = false
        }

        okButton = TextView(this)
        okButton.setText(getString(R.string.str_ok))
        okButton.setTextColor(Color.WHITE)
        okButton.setGravity(Gravity.END)
        okButton.setOnClickListener {
            updateData()
        }

        update_firstname.addTextChangedListener(this)
        update_lastname.addTextChangedListener(this)
        /*update_username.addTextChangedListener(this)*/
        /*update_email.addTextChangedListener(this)*/
        update_dateofbirthday.addTextChangedListener(this)

        update_dateofbirthday.setOnClickListener {
            DatePickerDialog(this, android.R.style.Theme_DeviceDefault_Dialog, DatePickerDialog.OnDateSetListener { datePicker, yearOfBirth, monthOfBirth, dayOfBirth ->
                update_dateofbirthday.setText("${dayOfBirth}/${monthOfBirth + 1}/${yearOfBirth}")
                year = yearOfBirth
                month = monthOfBirth
                dayOfMonth = dayOfBirth
            }, year, month, dayOfMonth).show()
        }
        profile_user_header_button_start.addView(backButton)
        database.listener.add(this)
        updateUser()
    }
}
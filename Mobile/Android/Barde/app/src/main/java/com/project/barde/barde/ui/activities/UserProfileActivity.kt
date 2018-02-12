package com.project.barde.barde.ui.activities

import android.os.Bundle
import android.support.annotation.StringRes
import android.support.v7.app.AppCompatActivity
import android.widget.DatePicker
import android.widget.Toast
import com.github.kittinunf.fuel.httpPost
import com.github.kittinunf.fuel.httpPut
import com.github.kittinunf.result.Result
import com.google.gson.Gson
import com.project.barde.barde.R
import com.project.barde.barde.db.UserDbHelper
import com.project.barde.barde.db.UserTable
import com.project.barde.barde.db.database
import com.project.barde.barde.model.Login
import kotlinx.android.synthetic.main.activity_login.*
import kotlinx.android.synthetic.main.activity_profile_user.*
import kotlinx.android.synthetic.main.activity_register.*
import org.jetbrains.anko.db.*
import java.util.*

/**
 * Created by michael on 11/11/2017.
 */

class UserProfileActivity : AppCompatActivity(), UserDbHelper.dataListener {
    override fun updateUser() {
        database.use {
            val c = rawQuery("SELECT * FROM user LIMIT 1", null)
            if(c.count >= 1){
                c.moveToFirst()
                update_email.setText(c.getString(c.getColumnIndex(UserTable.EMAIL)))
                update_password.setText(c.getString(c.getColumnIndex(UserTable.PASSWORD)))
                update_firstname.setText(c.getString(c.getColumnIndex(UserTable.FIRSTNAME)))
                update_lastname.setText(c.getString(c.getColumnIndex(UserTable.LASTNAME)))
                update_username.setText(c.getString(c.getColumnIndex(UserTable.USERNAME)))
                update_dateofbirthday.init(c.getInt(c.getColumnIndex(UserTable.YEAROFBIRTHDAY)), c.getInt(c.getColumnIndex(UserTable.MONTHOFBIRTHDAY)), c.getInt(c.getColumnIndex(UserTable.DAYOFBIRTHDAY)), null)
            }
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_profile_user)
        update_dateofbirthday.maxDate = Date().time
        database.listener.add(this)
        updateUser()
        updateInfo.setOnClickListener {
            "http://10.0.2.2:3000/user".httpPut(listOf("email" to update_email.text, "password" to update_password.text, "firstName" to update_firstname.text, "lastName" to update_lastname.text, "userName" to update_username.text, "yearOfBirth" to update_dateofbirthday.year, "monthOfBirth" to update_dateofbirthday.month, "dayOfBirth" to update_dateofbirthday.dayOfMonth)).responseString { request, response, result ->
                println("le response data")
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
                    Toast.makeText(this, "error", Toast.LENGTH_SHORT).show()
                }

            }
        }
    }
}
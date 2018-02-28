package com.project.barde.barde.ui.activities

import android.app.DatePickerDialog
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.widget.Toast
import com.github.kittinunf.fuel.httpPost
import com.github.kittinunf.result.Result
import com.google.gson.Gson
import com.project.barde.barde.R
import com.project.barde.barde.model.Login
import kotlinx.android.synthetic.main.activity_register.*
import org.jetbrains.anko.doAsync
import java.util.*

/**
 * Created by michael on 03/11/2017.
 */
class RegisterActivity : AppCompatActivity(){
    private var year = 0
    private var month = 0
    private var dayOfMonth = 0

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_register)
        val calendarInstance = Calendar.getInstance()
        val yearOfBirth = calendarInstance.get(Calendar.YEAR)
        val monthOfBirth = calendarInstance.get(Calendar.MONTH)
        val dayOfBirth = calendarInstance.get(Calendar.DAY_OF_MONTH)
        year = yearOfBirth
        month = monthOfBirth
        dayOfMonth = dayOfBirth
        register_dateofbirthday.setOnClickListener {
            DatePickerDialog(this, android.R.style.Theme_DeviceDefault_Dialog, DatePickerDialog.OnDateSetListener { datePicker, yearOfBirth, monthOfBirth, dayOfBirth ->
                register_dateofbirthday.setText("${dayOfBirth}/${monthOfBirth + 1}/${yearOfBirth}")
                year = yearOfBirth
                month = monthOfBirth
                dayOfMonth = dayOfBirth
            }, yearOfBirth, monthOfBirth, dayOfBirth).show()
        }
        toRegister.setOnClickListener{
            doAsync {
                StringBuilder(getString(R.string.api)).append("/auth/register").toString()
                        .httpPost(listOf("email" to register_email.text, "password" to register_password.text, "firstName" to register_firstname.text,
                                "lastName" to register_lastname.text, "userName" to register_username.text, "yearOfBirth" to year, "monthOfBirth" to month,
                                "dayOfBirth" to dayOfMonth)).responseString{ request, response, result ->
                    val register: Login = Gson().fromJson(String(response.data), Login::class.java)
                    Toast.makeText(this@RegisterActivity, register.data.message, Toast.LENGTH_SHORT).show()
                    when (result) {
                        is Result.Success -> {
                            finish()
                        }
                    }
                }
            }
        }
    }
}
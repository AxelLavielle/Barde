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
import java.util.regex.Pattern

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
            var datepicker = DatePickerDialog(this, android.R.style.Theme_DeviceDefault_Dialog, DatePickerDialog.OnDateSetListener { datePicker, yearOfBirth, monthOfBirth, dayOfBirth ->
                register_dateofbirthday.setText("${dayOfBirth}/${monthOfBirth + 1}/${yearOfBirth}")
                year = yearOfBirth
                month = monthOfBirth
                dayOfMonth = dayOfBirth
            }, yearOfBirth, monthOfBirth, dayOfBirth)
            datepicker.datePicker.maxDate = Date().time
            datepicker.show()
        }
        toRegister.setOnClickListener{
            if (register_firstname.text.isEmpty()){
                Toast.makeText(this@RegisterActivity, "FIrstname cannot be empty", Toast.LENGTH_SHORT).show()
            }else if (register_lastname.text.isEmpty()){
                Toast.makeText(this@RegisterActivity, "Lastname cannot be empty", Toast.LENGTH_SHORT).show()
            }else if (register_dateofbirthday.text.isEmpty()){
                Toast.makeText(this@RegisterActivity, "Birthday cannot be empty", Toast.LENGTH_SHORT).show()
            }else if (register_username.text.isEmpty()){
                Toast.makeText(this@RegisterActivity, "Username cannot be empty", Toast.LENGTH_SHORT).show()
            }else if (register_email.text.isEmpty()){
                Toast.makeText(this@RegisterActivity, "Email cannot be empty", Toast.LENGTH_SHORT).show()
            }else if (Pattern.compile(
                            "^(([\\w-]+\\.)+[\\w-]+|([a-zA-Z]|[\\w-]{2,}))@"
                                    + "((([0-1]?[0-9]{1,2}|25[0-5]|2[0-4][0-9])\\.([0-1]?"
                                    + "[0-9]{1,2}|25[0-5]|2[0-4][0-9])\\."
                                    + "([0-1]?[0-9]{1,2}|25[0-5]|2[0-4][0-9])\\.([0-1]?"
                                    + "[0-9]{1,2}|25[0-5]|2[0-4][0-9]))|"
                                    + "([a-zA-Z]+[\\w-]+\\.)+[a-zA-Z]{2,4})$"
                    ).matcher(register_email.text).matches() == false){
                Toast.makeText(this@RegisterActivity, "The email format is wrong.", Toast.LENGTH_SHORT).show()
            }else if (register_password.text.isEmpty()){
                Toast.makeText(this@RegisterActivity, "Password cannot be empty", Toast.LENGTH_SHORT).show()

            }else if (register_confirm_password.text.isEmpty()){
                Toast.makeText(this@RegisterActivity, "Please confirm your password", Toast.LENGTH_SHORT).show()

            }else if (register_password.text.toString() != register_confirm_password.text.toString()){
                Toast.makeText(this@RegisterActivity, "Password differ", Toast.LENGTH_SHORT).show()
            }else{
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
}
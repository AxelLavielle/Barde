package com.project.barde.barde.ui.activities

import android.app.DatePickerDialog
import android.content.Intent
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.text.InputType
import android.view.View
import android.widget.Toast
import com.github.kittinunf.fuel.core.FuelManager
import com.github.kittinunf.fuel.httpPost
import com.github.kittinunf.result.Result
import com.google.gson.Gson
import com.project.barde.barde.R
import com.project.barde.barde.db.database
import com.project.barde.barde.model.Login
import kotlinx.android.synthetic.main.activity_login.*
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
    private var firstPasswordShowed = false
    private var secondPasswordShowed = false

    override fun onCreate(savedInstanceState: Bundle?) {
        database.api = getString(R.string.api)
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
        changeShowFirstPassword.setOnClickListener {
            firstPasswordShowed = !firstPasswordShowed
            if (firstPasswordShowed){
                register_password.inputType =  InputType.TYPE_CLASS_TEXT or InputType.TYPE_TEXT_VARIATION_VISIBLE_PASSWORD
                changeShowFirstPassword.text = getString(R.string.str_hide)
            }else{
                register_password.inputType = InputType.TYPE_CLASS_TEXT or InputType.TYPE_TEXT_VARIATION_PASSWORD
                changeShowFirstPassword.text = getString(R.string.str_show)

            }
        }
        changeShowSecondPassword.setOnClickListener {
            secondPasswordShowed = !secondPasswordShowed
            if (secondPasswordShowed){
                register_confirm_password.inputType =  InputType.TYPE_CLASS_TEXT or InputType.TYPE_TEXT_VARIATION_VISIBLE_PASSWORD
                changeShowSecondPassword.text = getString(R.string.str_hide)

            }else{
                register_confirm_password.inputType = InputType.TYPE_CLASS_TEXT or InputType.TYPE_TEXT_VARIATION_PASSWORD
                changeShowSecondPassword.text = getString(R.string.str_show)

            }
        }

        toRegister.setOnClickListener{
            if (register_firstname.text.isEmpty()){
                Toast.makeText(this@RegisterActivity, getString(R.string.str_firstname_cannont_be_empy  ), Toast.LENGTH_SHORT).show()
            }else if (register_lastname.text.isEmpty()){
                Toast.makeText(this@RegisterActivity, getString(R.string.str_lastname_cannont_be_empy), Toast.LENGTH_SHORT).show()
            }else if (register_dateofbirthday.text.isEmpty()){
                Toast.makeText(this@RegisterActivity, getString(R.string.str_birthday_cannont_be_empy), Toast.LENGTH_SHORT).show()
            }else if (register_username.text.isEmpty()){
                Toast.makeText(this@RegisterActivity, getString(R.string.str_username_cannont_be_empy), Toast.LENGTH_SHORT).show()
            }else if (register_email.text.isEmpty()){
                Toast.makeText(this@RegisterActivity, getString(R.string.str_email_cannont_be_empy), Toast.LENGTH_SHORT).show()
            }else if (Pattern.compile(
                            "^(([\\w-]+\\.)+[\\w-]+|([a-zA-Z]|[\\w-]{2,}))@"
                                    + "((([0-1]?[0-9]{1,2}|25[0-5]|2[0-4][0-9])\\.([0-1]?"
                                    + "[0-9]{1,2}|25[0-5]|2[0-4][0-9])\\."
                                    + "([0-1]?[0-9]{1,2}|25[0-5]|2[0-4][0-9])\\.([0-1]?"
                                    + "[0-9]{1,2}|25[0-5]|2[0-4][0-9]))|"
                                    + "([a-zA-Z]+[\\w-]+\\.)+[a-zA-Z]{2,4})$"
                    ).matcher(register_email.text).matches() == false){
                Toast.makeText(this@RegisterActivity, getString(R.string.str_email_format_wrong), Toast.LENGTH_SHORT).show()
            }else if (register_password.text.isEmpty()){
                Toast.makeText(this@RegisterActivity, getString(R.string.str_password_cannont_be_empy), Toast.LENGTH_SHORT).show()

            }else if (register_confirm_password.text.isEmpty()){
                Toast.makeText(this@RegisterActivity, getString(R.string.str_please_confirm_your_password), Toast.LENGTH_SHORT).show()

            }else if (register_password.text.toString() != register_confirm_password.text.toString()){
                Toast.makeText(this@RegisterActivity, getString(R.string.str_password_dont_match), Toast.LENGTH_SHORT).show()
            }else{
                doAsync {
                    try{
                        StringBuilder(getString(R.string.api)).append("/auth/register").toString()
                                .httpPost(listOf("email" to register_email.text, "password" to register_password.text, "firstName" to register_firstname.text,
                                        "lastName" to register_lastname.text, "userName" to register_username.text, "yearOfBirth" to year, "monthOfBirth" to month,
                                        "dayOfBirth" to dayOfMonth)).responseString{ request, response, result ->
                                    println("tto = ")
                                    println(response)
                                    println("1------------")
                                    println(request)
                                    println("2------------")
                                    println(result)
                                    val register: Login = Gson().fromJson(String(response.data), Login::class.java)
                                    Toast.makeText(this@RegisterActivity, register.data.message, Toast.LENGTH_SHORT).show()
                                    when (result) {
                                        is Result.Success -> {
                                            StringBuilder(getString(R.string.api)).append("/auth/login").toString()
                                                    .httpPost(listOf("email" to register_email.text, "password" to register_password.text)).responseString{ request, response, result ->
                                                        if (!response.data.isEmpty()){
                                                            val login: Login = Gson().fromJson(String(response.data), Login::class.java)
                                                            Toast.makeText(this@RegisterActivity, login.data.message, Toast.LENGTH_SHORT).show()
                                                            when (result) {
                                                                is Result.Success -> {
                                                                    FuelManager.instance.baseHeaders = mapOf("Authorization" to login.data.token!!)
                                                                    database.updateUser()
                                                                    startActivity(Intent(this@RegisterActivity, MainActivity::class.java))
                                                                }
                                                            }
                                                        }
                                                        finish()

                                                    }
                                        }
                                    }
                                }
                    }catch (e : Exception){

                    }

                }
            }
        }
    }
    override fun onBackPressed() {
        startActivity(Intent(this, FirstPage::class.java))
        finish()
    }
}
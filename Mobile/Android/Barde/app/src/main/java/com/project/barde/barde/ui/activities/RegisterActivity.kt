package com.project.barde.barde.ui.activities

import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.widget.Toast
import com.github.kittinunf.fuel.httpPost
import com.github.kittinunf.result.Result
import com.google.gson.Gson
import com.project.barde.barde.R
import com.project.barde.barde.model.Login
import kotlinx.android.synthetic.main.activity_login.*
import kotlinx.android.synthetic.main.activity_register.*
import org.jetbrains.anko.doAsync

/**
 * Created by michael on 03/11/2017.
 */
class RegisterActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_register)
        toRegister.setOnClickListener{
            doAsync {
                "http://10.0.2.2:3000/auth/register".httpPost(listOf("email" to register_email.text, "password" to register_password.text, "firstName" to register_firstname.text, "lastName" to register_lastname.text, "userName" to register_username.text, "yearOfBirth" to register_dateofbirthday.year, "monthOfBirth" to register_dateofbirthday.month, "dayOfBirth" to register_dateofbirthday.dayOfMonth)).responseString{ request, response, result ->
                    val register: Login = Gson().fromJson(String(response.data), Login::class.java)
                     Toast.makeText(this@RegisterActivity, register.data.message, Toast.LENGTH_SHORT).show()
                     println(register)
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
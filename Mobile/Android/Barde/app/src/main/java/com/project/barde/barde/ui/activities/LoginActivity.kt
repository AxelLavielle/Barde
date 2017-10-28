package com.project.barde.barde.ui.activities

import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.text.Editable
import android.util.Log
import android.widget.Toast
import com.github.kittinunf.fuel.httpPost
import com.github.kittinunf.result.Result
import com.google.gson.Gson

import com.project.barde.barde.R
import com.project.barde.barde.User
import kotlinx.android.synthetic.main.activity_login.*
import org.jetbrains.anko.doAsync

data class Data(val token:String?, val message : String)
data class Login(val msg: String, val data: Data)

class LoginActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        val user: User
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_login)
        email.setText("toto@toto.com")
        password.setText("toto")
        connexion.setOnClickListener {
            doAsync {
                "http://10.0.2.2:3000/auth/login".httpPost(listOf("email" to email.text, "password" to password.text)).responseString{ request, response, result ->
                    when (result) {
                        is Result.Failure -> {
                            Toast.makeText(this@LoginActivity, "error", Toast.LENGTH_SHORT).show()

                        }
                        is Result.Success -> {
                            val json: Login = Gson().fromJson(result.get(), Login::class.java)
                            Toast.makeText(this@LoginActivity, json.data.message, Toast.LENGTH_SHORT).show()
                            finish()
                        }
                        }

                }
            }
        }
    }
}

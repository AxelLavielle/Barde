package com.project.barde.barde.ui.activities

import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.widget.Toast
import com.github.kittinunf.fuel.httpPost
import com.github.kittinunf.result.Result
import com.google.gson.Gson

import com.project.barde.barde.R
import com.project.barde.barde.model.User
import com.project.barde.barde.model.Login
import kotlinx.android.synthetic.main.activity_login.*
import org.jetbrains.anko.doAsync

class LoginActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        val user: User
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_login)
        //email.setText("toto@toto.com")
        //password.setText("toto")
        connexion.setOnClickListener {
            doAsync {
                "http://10.0.2.2:3000/auth/login".httpPost(listOf("email" to email.text, "password" to password.text)).responseString{ request, response, result ->
                    val login: Login = Gson().fromJson(String(response.data), Login::class.java)
                    Toast.makeText(this@LoginActivity, login.data.message, Toast.LENGTH_SHORT).show()
                    println(login)
                    when (result) {
                        is Result.Success -> {
                            finish()
                        }
                    }

                }
            }
        }
        register.setOnClickListener{
            val intent = Intent(this, RegisterActivity::class.java)
            startActivity(intent)
        }
    }
}

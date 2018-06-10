package com.project.barde.barde.ui.activities

import android.content.Context
import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.widget.Toast
import com.github.kittinunf.fuel.core.FuelManager
import com.github.kittinunf.fuel.httpPost
import com.github.kittinunf.result.Result
import com.google.gson.Gson

import com.project.barde.barde.R
import com.project.barde.barde.db.Synchro
import com.project.barde.barde.db.UserDbHelper
import com.project.barde.barde.db.database
import com.project.barde.barde.model.User
import com.project.barde.barde.model.Login
import kotlinx.android.synthetic.main.activity_login.*
import org.jetbrains.anko.doAsync
import org.jetbrains.anko.startActivity

class LoginActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        val user: User
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_login)
      email.setText("micha@barde.io")
        password.setText("titiletutu")
        /*email.setText("toto")
        password.setText("toto")*/
        connexion.setOnClickListener {
           // finish()//to remove
            doAsync {
                StringBuilder(getString(R.string.api)).append("/auth/login").toString()
                        .httpPost(listOf("email" to email.text, "password" to password.text)).responseString{ request, response, result ->
                    if (!response.data.isEmpty()){
                        val login: Login = Gson().fromJson(String(response.data), Login::class.java)
                        Toast.makeText(this@LoginActivity, login.data.message, Toast.LENGTH_SHORT).show()
                        when (result) {
                            is Result.Success -> {
                                FuelManager.instance.baseHeaders = mapOf("Authorization" to login.data.token!!)
                                database.updateUser()
                                finish()
                            }
                        }
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

package com.project.barde.barde.ui.activities

import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import com.github.kittinunf.fuel.core.FuelManager
import com.github.kittinunf.fuel.httpGet
import com.project.barde.barde.R
import com.project.barde.barde.db.UserDbHelper
import com.project.barde.barde.db.UserTable
import com.project.barde.barde.db.database
import kotlinx.android.synthetic.main.activity_first_page.*

class FirstPage : AppCompatActivity() {
    val back = false

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_first_page)
        database.api = getString(R.string.api)

        first_page_register.setOnClickListener {
            startActivity(Intent(this, RegisterActivity::class.java))
            finish()
        }
        first_page_login.setOnClickListener {
            startActivity(Intent(this, LoginActivity::class.java))
        }
        database.use {
            try {
                val c = rawQuery("SELECT * FROM me LIMIT 1", null)
                if (c.count >= 1) {
                    c.moveToFirst()
                    FuelManager.instance.baseHeaders = mapOf("Authorization" to c.getString(c.getColumnIndex(UserTable.TOKEN)))
                    StringBuilder(getString(R.string.api)).append("/user/me").toString()
                            .httpGet().responseString { request, response, result ->
                                if (response.statusCode == 200) {
                                    database.updateUser()
                                    startActivity(Intent(this@FirstPage, MainActivity::class.java))
                                    finish()
                                }
                            }
                }
            }catch (e : Exception){
                e.printStackTrace()
            }


        }
    }

    override fun onBackPressed() {
        if (back){
            super.onBackPressed()
        }
    }
}

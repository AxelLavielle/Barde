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

        first_page_register.setOnClickListener {
            startActivity(Intent(this, RegisterActivity::class.java))
            finish()
        }
        first_page_login.setOnClickListener {
            startActivity(Intent(this, LoginActivity::class.java))
            finish()
        }

    }

    override fun onBackPressed() {
        if (back){
            super.onBackPressed()
        }
    }
}

package com.project.barde.barde.ui.activities

import android.content.Intent
import android.net.ConnectivityManager
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import com.github.kittinunf.fuel.core.FuelManager
import com.project.barde.barde.R
import kotlinx.android.synthetic.main.activity_main.*

//import java.net.URL

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        startActivity(Intent(this, LoginActivity::class.java))
        setting.setOnClickListener {
            startActivity(Intent (this, UserProfileActivity::class.java))
        }
        logout.setOnClickListener {
            FuelManager.instance.baseHeaders = mapOf("Authorization" to "")
            startActivity(Intent(this, LoginActivity::class.java))
        }
    }

}

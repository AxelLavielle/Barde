package com.project.barde.barde.ui.activities

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.Toast
import com.project.barde.barde.R
import kotlinx.android.synthetic.main.activity_main.*
import org.jetbrains.anko.doAsync
import java.net.URL

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        connexion.setOnClickListener {
            Toast.makeText(this, "lol", 3).show()
            doAsync {
                val url = "http://samples.openweathermap.org/data/2.5/forecast?q=M%C3%BCnchen,DE&appid=b1b15e88fa797225412429c1c50c122a1"
                val test = URL(url).readText()
                Log.d(javaClass.simpleName, test)
            }
            /*
                call api authentification auth/login
                password : password
                email: email
             */
        }
    }

}

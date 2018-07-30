package com.project.barde.barde.ui.activities

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.support.v7.app.AlertDialog
import android.widget.Button
import android.widget.EditText
import android.widget.LinearLayout
import android.widget.Toast
import com.github.kittinunf.fuel.core.FuelManager
import com.github.kittinunf.fuel.httpPost
import com.github.kittinunf.result.Result
import com.google.gson.Gson
import com.project.barde.barde.R
import com.project.barde.barde.db.database
import com.project.barde.barde.model.Login
import kotlinx.android.synthetic.main.activity_login.*
import kotlinx.android.synthetic.main.activity_setting.*

class SettingActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_setting)
        setting_back.setOnClickListener {
            finish()
        }
        setting_report.setOnClickListener{
            val builder = AlertDialog.Builder(this)
            val inflater = layoutInflater
            val view = inflater.inflate(R.layout.dialog_report, null)
            builder.setView(view)
            val dialog = builder.create()
            dialog.show()
            val button = dialog.findViewById<Button>(R.id.submit_report)
            button!!.setOnClickListener {
                val msg = dialog.findViewById<EditText>(R.id.text_report)
                if (msg != null){
                    StringBuilder(getString(R.string.api)).append("/report").toString()
                            .httpPost(listOf("description" to msg.text)).responseString{ request, response, result ->
                                println(response.data)
                        val login: Login = Gson().fromJson(String(response.data), Login::class.java)
                        Toast.makeText(this, login.data.message, Toast.LENGTH_SHORT).show()
                        if (response.statusCode == 200){
                            dialog.dismiss()
                        }
                    }
                }
            }
        }
    }
}

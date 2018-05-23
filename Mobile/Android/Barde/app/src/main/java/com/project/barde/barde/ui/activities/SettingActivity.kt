package com.project.barde.barde.ui.activities

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.support.v7.app.AlertDialog
import android.widget.Button
import android.widget.EditText
import android.widget.Toast
import com.project.barde.barde.R
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
                dialog.dismiss()
                Toast.makeText(this, "report sent", Toast.LENGTH_SHORT).show()

            }
        }
    }
}

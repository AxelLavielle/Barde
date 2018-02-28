package com.project.barde.barde.ui.activities

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import com.project.barde.barde.R
import kotlinx.android.synthetic.main.activity_setting.*

class SettingActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_setting)
        setting_back.setOnClickListener {
            finish()
        }
    }
}

package com.project.barde.barde.ui.activities

import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.os.Handler
import com.github.kittinunf.fuel.core.FuelManager
import com.github.kittinunf.fuel.httpGet
import com.project.barde.barde.R
import com.project.barde.barde.db.UserTable
import com.project.barde.barde.db.database
import org.jetbrains.anko.db.INTEGER
import org.jetbrains.anko.db.PRIMARY_KEY
import org.jetbrains.anko.db.TEXT
import org.jetbrains.anko.db.createTable

class SplashActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        database.api = getString(R.string.api)

        setContentView(R.layout.activity_splash)
        database.use {
            createTable("me", true,
                    UserTable.ID to INTEGER + PRIMARY_KEY,
                    UserTable.PASSWORD to TEXT,
                    UserTable.FIRSTNAME to TEXT,
                    UserTable.LASTNAME to TEXT,
                    UserTable.USERNAME to TEXT,
                    UserTable.DAYOFBIRTHDAY to INTEGER,
                    UserTable.MONTHOFBIRTHDAY to INTEGER,
                    UserTable.YEAROFBIRTHDAY to INTEGER,
                    UserTable.ROLE to TEXT,
                    UserTable.TOKEN to TEXT,
                    UserTable.EMAIL to TEXT)
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
                                    startActivity(Intent(this@SplashActivity, MainActivity::class.java))
                                    finish()
                                }else{
                                    startFirstPageActivity()
                                }
                            }
                }else{
                    startFirstPageActivity()

                }
            }catch (e : Exception){
                e.printStackTrace()
                startFirstPageActivity()

            }

        }



    }

    fun startFirstPageActivity(){
        Handler().postDelayed({
            startActivity(Intent(this@SplashActivity, FirstPage::class.java))
            finish()
        },1000)
    }

}

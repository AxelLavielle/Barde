package com.project.barde.barde.ui.activities

import android.os.Bundle
import android.support.annotation.StringRes
import android.support.v7.app.AppCompatActivity
import android.widget.DatePicker
import android.widget.Toast
import com.project.barde.barde.R
import com.project.barde.barde.db.UserTable
import com.project.barde.barde.db.database
import kotlinx.android.synthetic.main.activity_profile_user.*
import org.jetbrains.anko.db.*
import java.util.*

/**
 * Created by michael on 11/11/2017.
 */

class UserProfileActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_profile_user)
        database.use {
           /* insert("user",
                    UserTable.EMAIL to "toto",
                    UserTable.PASSWORD to "toto",
                    UserTable.FIRSTNAME to "toto",
                    UserTable.LASTNAME to "toto",
                    UserTable.USERNAME to "toto")*/
s            val c = rawQuery("SELECT * FROM user LIMIT 1", null)
            if(c.count >= 1){
                c.moveToFirst()
                update_email.setText(c.getString(c.getColumnIndex(UserTable.EMAIL)))
                update_password.setText(c.getString(c.getColumnIndex(UserTable.PASSWORD)))
                update_firstname.setText(c.getString(c.getColumnIndex(UserTable.FIRSTNAME)))
                update_lastname.setText(c.getString(c.getColumnIndex(UserTable.LASTNAME)))
                update_username.setText(c.getString(c.getColumnIndex(UserTable.USERNAME)))
                update_dateofbirthday.init(c.getInt(c.getColumnIndex(UserTable.YEAROFBIRTHDAY)), c.getInt(c.getColumnIndex(UserTable.MONTHOFBIRTHDAY)), c.getInt(c.getColumnIndex(UserTable.DAYOFBIRTHDAY)), null)
            }
        }
        updateInfo.setOnClickListener {
            database.use {
                update("user", UserTable.EMAIL to update_email.text.toString(), UserTable.PASSWORD to update_password.text.toString(), UserTable.FIRSTNAME to update_firstname.text.toString(),
                        UserTable.LASTNAME to update_lastname.text.toString(), UserTable.USERNAME to update_username.text.toString(), UserTable.DAYOFBIRTHDAY to update_dateofbirthday.dayOfMonth,
                        UserTable.MONTHOFBIRTHDAY to update_dateofbirthday.month, UserTable.YEAROFBIRTHDAY to update_dateofbirthday.year)
                        .whereSimple("_id = 1 OR 1")
                        .exec()
                Toast.makeText(this@UserProfileActivity, "str_successuful_update", Toast.LENGTH_SHORT).show()
                finish()

            }
        }
    }
}
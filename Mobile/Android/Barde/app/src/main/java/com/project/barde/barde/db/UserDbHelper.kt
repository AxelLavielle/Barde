package com.project.barde.barde.db

import android.content.Context
import android.database.Cursor
import android.database.sqlite.SQLiteDatabase
import com.github.kittinunf.fuel.core.FuelManager
import com.github.kittinunf.fuel.httpGet
import com.github.kittinunf.fuel.httpPut
import com.google.gson.Gson
import com.project.barde.barde.model.RequestMe
import org.jetbrains.anko.db.*
import java.text.SimpleDateFormat
import java.time.LocalDate
import java.util.*

/**
 * Created by michael on 11/11/2017.
 */
class UserDbHelper(ctx: Context) : ManagedSQLiteOpenHelper(ctx, "user.db", null, 1) {
    var listener = arrayListOf<dataListener>()
    companion object {
        private var instance: UserDbHelper? = null
        /*private val listener = arrayListOf<Any>()*/
        @Synchronized
        fun getInstance(ctx: Context): UserDbHelper {
            if (instance == null) {
                instance = UserDbHelper(ctx.getApplicationContext())
            }
            return instance!!
        }
    }

    interface dataListener {
        fun updateUser()
    }

    override fun onCreate(db: SQLiteDatabase) {
        db.createTable("user", true,
                UserTable.ID to INTEGER + PRIMARY_KEY,
                UserTable.PASSWORD to TEXT,
                UserTable.FIRSTNAME to TEXT,
                UserTable.LASTNAME to TEXT,
                UserTable.USERNAME to TEXT,
                UserTable.DAYOFBIRTHDAY to INTEGER,
                UserTable.MONTHOFBIRTHDAY to INTEGER,
                UserTable.YEAROFBIRTHDAY to INTEGER,
                UserTable.ROLE to TEXT,
                UserTable.EMAIL to TEXT)
    }

    override fun onUpgrade(db: SQLiteDatabase, oldVersion: Int, newVersion: Int) {
    }

    /*fun addListener(func : Any){
        listener.add(func)
    }*/

    fun updateUser () {
        "http://10.0.2.2:3000/user/me".httpGet().responseString { request, response, result ->
            val requestMe: RequestMe
            requestMe = Gson().fromJson(String(response.data), RequestMe::class.java)
            val user = requestMe.data.user
            val c = this.readableDatabase.rawQuery("SELECT * FROM user LIMIT 1", null)

            val cal = Calendar.getInstance()
            cal.setTime(user.dateOfBirth)
            if (c.count >= 1){
                this.writableDatabase.update("user",
                        UserTable.EMAIL to user.email,
                        UserTable.PASSWORD to "toto",
                        UserTable.FIRSTNAME to user.name.firstName,
                        UserTable.LASTNAME to user.name.lastName,
                        UserTable.DAYOFBIRTHDAY to cal.get(Calendar.DAY_OF_MONTH),
                        UserTable.MONTHOFBIRTHDAY to cal.get(Calendar.MONTH),
                        UserTable.YEAROFBIRTHDAY to cal.get(Calendar.YEAR),
                        UserTable.USERNAME to user.name.userName).whereSimple("_id = 1 OR 1").exec()
            }else {
                this.writableDatabase.insert("user",
                        UserTable.EMAIL to user.email,
                        UserTable.PASSWORD to "toto",
                        UserTable.FIRSTNAME to user.name.firstName,
                        UserTable.LASTNAME to user.name.lastName,
                        UserTable.DAYOFBIRTHDAY to cal.get(Calendar.DAY_OF_MONTH),
                        UserTable.MONTHOFBIRTHDAY to cal.get(Calendar.MONTH),
                        UserTable.YEAROFBIRTHDAY to cal.get(Calendar.YEAR),
                        UserTable.USERNAME to user.name.userName)
            }
            if (!listener.isEmpty()){
                for (l in listener){
                    l?.updateUser()
                }
            }
        }
        /*for (l in listener){
            l
        }*/
    }
}

val Context.database: UserDbHelper
    get() = UserDbHelper.getInstance(getApplicationContext())
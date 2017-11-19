package com.project.barde.barde.db

import android.content.Context
import android.database.sqlite.SQLiteDatabase
import org.jetbrains.anko.db.*

/**
 * Created by michael on 11/11/2017.
 */
class UserDbHelper(ctx: Context) : ManagedSQLiteOpenHelper(ctx, "user.db", null, 1) {
    companion object {
        private var instance: UserDbHelper? = null

        @Synchronized
        fun getInstance(ctx: Context): UserDbHelper {
            if (instance == null) {
                instance = UserDbHelper(ctx.getApplicationContext())
            }
            return instance!!
        }
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
}

val Context.database: UserDbHelper
    get() = UserDbHelper.getInstance(getApplicationContext())
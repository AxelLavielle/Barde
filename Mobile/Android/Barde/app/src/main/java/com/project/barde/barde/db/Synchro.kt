package com.project.barde.barde.db

import android.content.Context
import android.view.View
import android.view.ViewGroup
import android.widget.BaseAdapter
import com.github.kittinunf.fuel.core.FuelManager
import com.github.kittinunf.fuel.httpGet
import com.google.gson.Gson
import com.project.barde.barde.db.database

import com.project.barde.barde.model.RequestMe

/**
 * Created by michael on 15/01/2018.
 */
class Synchro{
    var context: Context? = null
    constructor(context: Context){
        this.context = context
    }
    fun user (token: String, any: Any) {
        FuelManager.instance.baseHeaders = mapOf("Authorization" to token)
        "http://10.0.2.2:3000/user/me".httpGet().responseString { request, response, result ->
            val requestMe: RequestMe
            requestMe = Gson().fromJson(String(response.data), RequestMe::class.java)
            println(String(response.data))
            println(requestMe)
           /*database.use {
                val user = requestMe.data.user
                insert("user",
                         UserTable.EMAIL to user.email,
                         UserTable.PASSWORD to "toto",
                         UserTable.FIRSTNAME to user.name.firstname,
                         UserTable.LASTNAME to user.name.lastName,
                         UserTable.USERNAME to user.name.userName)
            }*/
        }
    }

    fun setting(){

    }
}
package com.project.barde.barde.model

/**
 * Created by michael on 04/11/2017.
 */

data class Data(val token:String?, val message : String)
data class Login(val msg: String, val data: Data)

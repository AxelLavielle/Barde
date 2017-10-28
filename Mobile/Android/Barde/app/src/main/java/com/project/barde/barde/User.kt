package com.project.barde.barde

/**
 * Created by michael on 27/10/2017.
 */
data class Identity(val FirstName: String, val LasName: String, val UserName: String, val Role: String)
data class User(val email:String, val password: String, val token:String)
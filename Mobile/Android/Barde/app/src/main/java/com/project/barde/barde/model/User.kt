package com.project.barde.barde.model

import java.util.*

/**
 * Created by michael on 27/10/2017.
 */
data class Identity(val _id: String, val password: String, val firstname: String, val lastname: String, val username: String, val dateOfBirth: Date, val role: String, val email: String)
data class Name(val userName: String, val lastName: String, val firstName: String)
data class RequestMe(val msg: String, val data: DataR)
data class DataR(val user: User)
data class User(val role: String, val name: Name, val email:String, val dateOfBirth: Date)
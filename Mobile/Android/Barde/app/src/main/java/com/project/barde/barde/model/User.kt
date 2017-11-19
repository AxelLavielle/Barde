package com.project.barde.barde.model

import java.util.*

/**
 * Created by michael on 27/10/2017.
 */
data class Identity(val _id: String, val password: String, val firstname: String, val lastname: String, val username: String, val dateOfBirth: Date, val role: String, val email: String)
data class User(val email:String, val password: String, val token:String)
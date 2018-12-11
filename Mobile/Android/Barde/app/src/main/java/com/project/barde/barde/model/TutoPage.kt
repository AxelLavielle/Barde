package com.project.barde.barde.model

data class TutoPage(val title : String, val subTitle : String, val imageId: Int, val text : String, val listener: Listener)

interface Listener {
    fun onCLick()
}
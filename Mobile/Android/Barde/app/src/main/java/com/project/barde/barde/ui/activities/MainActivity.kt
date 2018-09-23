package com.project.barde.barde.ui.activities

import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.support.v4.app.Fragment
import com.project.barde.barde.R
import com.project.barde.barde.db.database
import com.project.barde.barde.ui.fragments.GenerationFragment
import com.project.barde.barde.ui.fragments.MyListsFragment
import com.project.barde.barde.ui.fragments.PlaylistFragment
import com.project.barde.barde.ui.fragments.UserPageFragment
import kotlinx.android.synthetic.main.activity_main.*

//import java.net.URL

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        database.api = getString(R.string.api)
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        val myLists = MyListsFragment()
        val profile = UserPageFragment()
        val playlist = PlaylistFragment()
        val generation = GenerationFragment()
        //startActivity(Intent(this, FirstPage::class.java))
        supportFragmentManager.beginTransaction()
                .add(R.id.container, playlist as Fragment)
                .commit()
        buttonNavigationMenu.setOnNavigationItemSelectedListener{item ->
            when (item.itemId){
                R.id.menu_profile -> {
                    supportFragmentManager.beginTransaction()
                            .replace(R.id.container, profile as Fragment)
                            .commit()
                }
                /*R.id.menu_my_list -> {
                    supportFragmentManager.beginTransaction()
                            .replace(R.id.container, myLists as Fragment)
                            .commit()
                }*/
               R.id.menu_playlist -> {
                    supportFragmentManager.beginTransaction()
                            .replace(R.id.container, playlist as Fragment)
                            .commit()
                }
                R.id.menu_generation -> {
                    supportFragmentManager.beginTransaction()
                            .replace(R.id.container, generation as Fragment)
                            .commit()
                }
            }
            return@setOnNavigationItemSelectedListener true
        }
    }

    override fun onBackPressed() {
        val b = false
        if (b){
            super.onBackPressed()
        }
    }

}
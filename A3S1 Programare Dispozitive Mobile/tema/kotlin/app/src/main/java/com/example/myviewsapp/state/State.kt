package com.example.myviewsapp.state

import android.content.Intent

data class State(
    val jwt: String,
) {
    constructor(intent: Intent) : this(intent.extras!!.getString("jwt")!!) {

    }

    fun addToIntent(intent: Intent) {
        intent.putExtra("jwt", jwt)
    }
}

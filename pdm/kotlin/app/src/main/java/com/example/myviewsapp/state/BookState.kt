package com.example.myviewsapp.state

import android.content.Intent

data class BookState(
    val id: Int,
    val title: String,
    val rating: Int,
    val read: Boolean,
) {

    constructor(intent: Intent)
    : this(
        intent.extras!!.getInt("id"),
        intent.extras!!.getString("title")!!,
        intent.extras!!.getInt("rating"),
        intent.extras!!.getBoolean("read"),
    ) { }

    fun addToIntent(intent: Intent) {
        intent.putExtra("id", id)
        intent.putExtra("title", title)
        intent.putExtra("rating", rating)
        intent.putExtra("read", read)
    }
}

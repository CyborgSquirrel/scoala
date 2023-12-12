package com.example.myviewsapp

import android.os.Bundle
import android.util.Log
import android.widget.Button
import android.widget.CheckBox
import android.widget.RatingBar
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import com.example.myviewsapp.dto.PutBook
import com.example.myviewsapp.state.BookState
import com.example.myviewsapp.state.State
import retrofit2.create
import kotlin.concurrent.thread

class EditActivity : AppCompatActivity() {
    lateinit var state: State
    lateinit var bookState: BookState
    lateinit var client: TheApi

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        state = State(intent)
        bookState = BookState(intent)
        client = Api.retrofit(jwt = state.jwt).create()

        setContentView(R.layout.edit_activity)

        val editTextTitle = findViewById<TextView>(R.id.editTextTitle)
        val ratingBar = findViewById<RatingBar>(R.id.ratingBar)
        val checkBoxRead = findViewById<CheckBox>(R.id.checkBoxRead)

        editTextTitle.text = bookState.title
        ratingBar.rating = bookState.rating.toFloat()
        checkBoxRead.isChecked = bookState.read

        val buttonSubmit = findViewById<Button>(R.id.buttonSubmit)
        buttonSubmit.setOnClickListener {
            thread {
                client.putBook(
                    bookState.id,
                    PutBook(
                        editTextTitle.text.toString(),
                        checkBoxRead.isChecked,
                        ratingBar.rating.toInt())
                ).execute()
            }.join()
            finish()
        }
    }
}
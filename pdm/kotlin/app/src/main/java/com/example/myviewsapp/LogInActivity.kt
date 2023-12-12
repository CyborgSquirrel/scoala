package com.example.myviewsapp

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.Button
import android.widget.EditText
import androidx.room.Room
import com.example.myviewsapp.dto.Book
import com.example.myviewsapp.dto.PostUserLogin
import com.example.myviewsapp.state.State
import retrofit2.create
import kotlin.concurrent.thread

class LogInActivity : AppCompatActivity() {
    private var client = Api.retrofit().create<TheApi>()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_log_in)
        findViewById<Button>(R.id.logInButton).setOnClickListener {
            thread {
                val name = findViewById<EditText>(R.id.nameEdit).text.toString()
                val password = findViewById<EditText>(R.id.passwordEdit).text.toString()
                val response = client.postUserLogin(PostUserLogin(name, password)).execute()
                if (!response.isSuccessful) return@thread;

                val loginResponse = response.body();
                Log.i(TAG, loginResponse!!.access_token)
                val intent = Intent(this, HomeActivity::class.java)
                val state = State(loginResponse.access_token)
                state.addToIntent(intent)
                startActivity(intent)
            }
        }
        Log.i(TAG, "onCreate")
    }

    override fun onRestart() {
        super.onRestart()
        Log.i(TAG, "onRestart")
    }

    override fun onStart() {
        super.onStart()
        Log.i(TAG, "onStart")
    }

    override fun onResume() {
        super.onResume()
        Log.i(TAG, "onResume")
    }

    override fun onPause() {
        super.onPause()
        Log.i(TAG, "onPause")
    }

    override fun onStop() {
        super.onStop()
        Log.i(TAG, "onStop")
    }

    override fun onSaveInstanceState(outState: Bundle) {
        Log.i(TAG, "onSaveInstanceState")
        super.onSaveInstanceState(outState)
    }

    override fun onDestroy() {
        super.onDestroy()
        Log.i(TAG, "onDestroy")
    }
}

val Any.TAG: String
    get() {
        val tag = javaClass.simpleName
        return if (tag.length <= 23) tag else tag.substring(0, 23)
    }

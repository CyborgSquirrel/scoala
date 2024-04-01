package com.example.myviewsapp

import android.content.Context
import android.graphics.Interpolator
import android.os.Bundle
import android.util.Log
import android.view.View
import android.view.animation.AccelerateInterpolator
import android.widget.Button
import android.widget.CheckBox
import android.widget.RatingBar
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.NotificationCompat
import androidx.core.app.NotificationManagerCompat
import androidx.work.Constraints
import androidx.work.Data
import androidx.work.NetworkType
import androidx.work.OneTimeWorkRequest
import androidx.work.OneTimeWorkRequestBuilder
import androidx.work.WorkManager
import androidx.work.Worker
import androidx.work.WorkerParameters
import com.example.myviewsapp.dto.PutBook
import com.example.myviewsapp.state.BookState
import com.example.myviewsapp.state.State
import com.google.android.gms.maps.CameraUpdateFactory
import com.google.android.gms.maps.GoogleMap
import com.google.android.gms.maps.OnMapReadyCallback
import com.google.android.gms.maps.SupportMapFragment
import com.google.android.gms.maps.model.LatLng
import com.google.android.gms.maps.model.Marker
import com.google.android.gms.maps.model.MarkerOptions
import retrofit2.create
import kotlin.concurrent.thread


class Worker(appContext: Context, workerParameters: WorkerParameters):
    androidx.work.Worker(appContext, workerParameters) {

    lateinit var client: TheApi

    override fun doWork(): Result {
        client = Api.retrofit(jwt = inputData.getString("jwt")!!).create()

        // this *SUCKS*

        // I have to write all this boilerplate
        // to pass all this garbage to this damn worker

        // why isn't there some kind of annotation for you to put on a class,
        // that would give it a function for automatically (de)serializing
        // from this androidx.work.Data thing

        // AND you have to pass a default value to all these getters
        // I want for it to break if the key is missing.
        // I don't want to get bugs because of these damn default values.

        // </rant>
        client.putBook(
            inputData.getInt("id", -1),
            PutBook(
                inputData.getString("title")!!,
                inputData.getBoolean("read", false),
                inputData.getInt("rating", -1),
                inputData.getDouble("lat", 0.0),
                inputData.getDouble("lng", 0.0),
            )
        ).execute()

        Api.dataRefreshed.open()

        val notification = NotificationCompat.Builder(
            applicationContext,
            applicationContext.getString(R.string.channel_name))
            .setSmallIcon(R.drawable.ic_launcher_foreground)
            .setContentTitle("Finished uploading book")
            .build();
        with (NotificationManagerCompat.from(this.applicationContext)) {
            // hahahaha
            // stupid api, tremble before an even stupider solution
            val id = System.currentTimeMillis().toInt();
            notify(id, notification)
        }

        return Result.success()
    }
}

class EditActivity : AppCompatActivity() {
    lateinit var state: State
    lateinit var bookState: BookState

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        state = State(intent)
        bookState = BookState(intent)

        setContentView(R.layout.edit_activity)
        val contentView = findViewById<View>(android.R.id.content);

        contentView.apply {
            alpha = 0f
            visibility = View.VISIBLE

            animate()
                .alpha(1f)
                .setInterpolator(AccelerateInterpolator())
                .setDuration(2000)
                .setListener(null)
        }

        val editTextTitle = findViewById<TextView>(R.id.editTextTitle)
        val ratingBar = findViewById<RatingBar>(R.id.ratingBar)
        val checkBoxRead = findViewById<CheckBox>(R.id.checkBoxRead)
        val mapFragment = supportFragmentManager.findFragmentById(R.id.map) as SupportMapFragment

        editTextTitle.text = bookState.title
        ratingBar.rating = bookState.rating.toFloat()
        checkBoxRead.isChecked = bookState.read

        var marker: Marker? = null;
        mapFragment.getMapAsync { map ->
            val latLng = LatLng(bookState.lat, bookState.lng)
            marker = map.addMarker(MarkerOptions().position(latLng))
            map.moveCamera(CameraUpdateFactory.newLatLng(latLng))
            map.setOnMapClickListener { point ->
                marker?.remove()
                marker = map.addMarker(MarkerOptions().position(point))
            }
        }

        val buttonSubmit = findViewById<Button>(R.id.buttonSubmit)
        buttonSubmit.setOnClickListener {
            if (marker == null) return@setOnClickListener;

            WorkManager.getInstance(applicationContext)
                .enqueue(
                    OneTimeWorkRequestBuilder<com.example.myviewsapp.Worker>()
                        .setConstraints(
                            Constraints.Builder()
                                .setRequiredNetworkType(NetworkType.CONNECTED)
                                .build())
                        .setInputData(
                            Data.Builder()
                                .putInt("id", bookState.id)
                                .putString("title", editTextTitle.text.toString())
                                .putBoolean("read", checkBoxRead.isChecked)
                                .putInt("rating", ratingBar.rating.toInt())
                                .putString("jwt", state.jwt)
                                .putDouble("lat", marker!!.position.latitude)
                                .putDouble("lng", marker!!.position.longitude)
                                .build()
                        )
                        .build())

            finish()
        }
    }
}
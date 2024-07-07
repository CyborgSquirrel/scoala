package com.example.myviewsapp

import android.graphics.Color
import android.hardware.Sensor
import android.hardware.SensorEvent
import android.hardware.SensorEventListener
import android.hardware.SensorManager
import android.hardware.TriggerEvent
import android.hardware.TriggerEventListener
import android.net.ConnectivityManager
import android.net.Network
import android.net.NetworkCapabilities
import android.net.NetworkRequest
import android.util.Log
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity

object NetworkStatus {
    fun setup(activity: AppCompatActivity) {
        val networkRequest = NetworkRequest.Builder()
            .addCapability(NetworkCapabilities.NET_CAPABILITY_INTERNET)
            .build();

        val networkCallback = object : ConnectivityManager.NetworkCallback() {
            override fun onAvailable(network: Network) {
                super.onAvailable(network)
                activity.runOnUiThread {
                    val textView = activity.findViewById<TextView>(R.id.networkStatus) ?: return@runOnUiThread
                    textView.text = "connected"
                    textView.setTextColor(Color.GREEN)
                }
            }

            override fun onLost(network: Network) {
                super.onLost(network)
                activity.runOnUiThread {
                    val textView = activity.findViewById<TextView>(R.id.networkStatus) ?: return@runOnUiThread
                    textView.text = "disconnected"
                    textView.setTextColor(Color.RED)
                }
            }
        }

        val connectivityManager =
            activity.getSystemService(ConnectivityManager::class.java) as ConnectivityManager
        connectivityManager.requestNetwork(networkRequest, networkCallback)

        val textView = activity.findViewById<TextView>(R.id.networkStatus)
        textView.apply {
            animate()
                .rotation(10f)
                .setDuration(2000)
                .setListener(null)
                .withEndAction {
                    animate()
                        .rotation(-10f)
                        .setDuration(2000)
                        .setListener(null)
                }
        }

        val sensorManager = activity.getSystemService(SensorManager::class.java) as SensorManager
        val sensor: Sensor? = sensorManager.getDefaultSensor(Sensor.TYPE_LINEAR_ACCELERATION)

        Log.i("asd", sensor.toString())
        val triggerEventListener = object : SensorEventListener {
            var lastUpdate: Long? = null

            override fun onSensorChanged(event: SensorEvent?) {
                if (event != null) {
                    val mag = Math.sqrt(
                            Math.pow(event.values[0].toDouble(), 2.0)
                            + Math.pow(event.values[1].toDouble(), 2.0)
                            + Math.pow(event.values[2].toDouble(), 2.0)
                            )

                    val now = System.currentTimeMillis()
                    if (mag > 5.0 && (lastUpdate == null || now - lastUpdate!! > 1000)) {
                        lastUpdate = now
                        activity.runOnUiThread {
                            val textView = activity.findViewById<TextView>(R.id.networkStatus)
                            textView.apply {
                                rotation = 0f
                                animate()
                                    .rotation(360f)
                                    .setDuration(2000)
                                    .setListener(null)
                            }
                        }
                    }
//                    Log.i("asd", event.values[0].toString())
                }
            }

            override fun onAccuracyChanged(sensor: Sensor?, accuracy: Int) {
                // TODO("Not yet implemented")
            }
        }
        sensor?.also { sensor ->
            sensorManager.registerListener(
                triggerEventListener,
                sensor,
                SensorManager.SENSOR_DELAY_NORMAL,
                SensorManager.SENSOR_DELAY_UI,
            )
        }
    }
}
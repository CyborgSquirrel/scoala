package com.example.myviewsapp

import android.util.Log
import androidx.room.Room
import com.google.gson.GsonBuilder
import okhttp3.Interceptor
import okhttp3.OkHttpClient
import okhttp3.Response
import retrofit2.Retrofit
import retrofit2.converter.gson.GsonConverterFactory

object Api {
//    private val url = "192.168.0.194:5000"
    private val url = "172.20.10.2:5000"
    private val httpUrl = "http://$url/"

    private val gson = GsonBuilder().create()

    fun retrofit(
        jwt: String? = null,
    ): Retrofit {
        val clientBuilder = OkHttpClient.Builder()
        Log.i("interceptron", "hello")
        if (jwt != null) {
            Log.i("interceptron", "adding")
            val interceptor = object : Interceptor {
                override fun intercept(chain: Interceptor.Chain): Response {
                    val request = chain.request()
                    Log.i("interceptron", "intercepting")
                    val newRequest = request.newBuilder()
                        .header("Authorization", " Bearer $jwt")
                        .build()
                    return chain.proceed(newRequest)
                }
            }
            clientBuilder.addInterceptor(interceptor)
        }
        val client = clientBuilder.build()

        val retrofit = Retrofit.Builder()
            .client(client)
            .baseUrl(httpUrl)
            .addConverterFactory(GsonConverterFactory.create(gson))

        return retrofit.build();
    }
}
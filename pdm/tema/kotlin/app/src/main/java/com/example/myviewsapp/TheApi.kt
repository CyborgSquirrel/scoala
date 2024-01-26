package com.example.myviewsapp

import com.example.myviewsapp.dto.Book
import com.example.myviewsapp.dto.LoginResponse
import com.example.myviewsapp.dto.PostUserLogin
import com.example.myviewsapp.dto.PutBook
import retrofit2.Call
import retrofit2.http.Body
import retrofit2.http.GET
import retrofit2.http.POST
import retrofit2.http.PUT
import retrofit2.http.Path

interface TheApi {
    @POST("/user/login")
    fun postUserLogin(@Body body: PostUserLogin): Call<LoginResponse>

    @GET("/book")
    fun getBooks(): Call<List<Book>>

    @PUT("/book/{id}")
    fun putBook(@Path("id") id: Int, @Body body: PutBook): Call<Unit>
}
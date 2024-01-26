package com.example.myviewsapp.dto

data class PutBook(
    val title: String,
    val read: Boolean,
    val rating: Int,
    val lat: Double,
    val lng: Double,
)
package com.example.myviewsapp.dto

import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity(tableName = "Book")
data class Book(
    @PrimaryKey val id: Int,
    val read: Boolean,
    val title: String,
    val rating: Int,
    val date_added: Long,
    val lat: Float,
    val lng: Float,
)

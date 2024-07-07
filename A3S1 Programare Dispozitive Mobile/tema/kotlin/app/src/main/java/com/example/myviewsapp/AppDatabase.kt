package com.example.myviewsapp

import androidx.room.Database
import androidx.room.RoomDatabase
import com.example.myviewsapp.dto.Book
import com.example.myviewsapp.dto.BookDao

@Database(entities = [Book::class], version = 1)
abstract class AppDatabase : RoomDatabase() {
    abstract fun bookDao(): BookDao
}
package com.example.myviewsapp

import android.content.Context
import androidx.room.Room
import androidx.startup.Initializer

class AppDatabaseInitializer : Initializer<AppDatabase> {
    override fun create(context: Context): AppDatabase {
        return Room.databaseBuilder(
            context,
            AppDatabase::class.java, "database"
        ).build()
    }

    override fun dependencies(): List<Class<out Initializer<*>>> {
        return emptyList()
    }
}
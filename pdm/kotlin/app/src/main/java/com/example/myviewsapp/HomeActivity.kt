package com.example.myviewsapp

import android.content.Context
import android.content.Intent
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.AdapterView
import android.widget.ArrayAdapter
import android.widget.ListView
import android.widget.RatingBar
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import androidx.room.Room
import com.example.myviewsapp.dto.Book
import com.example.myviewsapp.state.BookState
import com.example.myviewsapp.state.State
import retrofit2.create
import java.text.SimpleDateFormat
import java.util.Date
import kotlin.concurrent.thread

class HomeActivity : AppCompatActivity() {
    lateinit var state: State
    lateinit var client: TheApi

    class Adapter(context: Context, val resource: Int, val client: TheApi) : ArrayAdapter<Book>(context, resource) {
        var items: List<Book>? = null
        val dateFormat = SimpleDateFormat("dd/MM/yyyy")

        fun initItems() {
            if (items == null) {
                thread {
                    val response = client.getBooks().execute()
                    if (!response.isSuccessful) {
                        items = emptyList()
                        return@thread
                    }
                    items = response.body()!!
                    return@thread
                }.join()
            }
        }

        override fun getCount(): Int {
            initItems()
            return items!!.size
        }

        override fun getItem(position: Int): Book? {
            initItems()
            return items!!.getOrNull(position)
        }

        override fun getView(position: Int, convertView: View?, parent: ViewGroup): View {
            val item = getItem(position)!!

            val inflater = LayoutInflater.from(context)
            val rowView = inflater.inflate(resource, parent, false)

            val textViewTitle = rowView.findViewById<TextView>(R.id.textViewTitle)
            textViewTitle.text = item.title

            val ratingBar = rowView.findViewById<RatingBar>(R.id.ratingBar2)
            ratingBar.rating = item.rating.toFloat()

            val textViewDateAdded = rowView.findViewById<TextView>(R.id.textViewDateAdded)
            textViewDateAdded.text = dateFormat.format(Date(item.date_added * 1000))

            val textViewRead = rowView.findViewById<TextView>(R.id.textViewRead)
            textViewRead.text = if (item.read) "Read: ☑" else "Read: ☐"

            return rowView
        }
    }

    lateinit var adapter: Adapter

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

//        val db = Room.databaseBuilder(
//            applicationContext,
//            AppDatabase::class.java, "database"
//        ).build()
//        db.bookDao().insert(Book(1, true, "test", 3, 1600000, 0.2f, 0.3f))

        state = State(intent)
        client = Api.retrofit(jwt = state.jwt).create()

        setContentView(R.layout.activity_home)

        val outer = this

        adapter = Adapter(applicationContext, R.layout.item_layout, client)

        val listView = findViewById<ListView>(R.id.bookListView)
        listView.adapter = adapter
        listView.onItemClickListener = object : AdapterView.OnItemClickListener {
            override fun onItemClick(adapter: AdapterView<*>?, view: View?, position: Int, p3: Long) {
                if (adapter == null) return
                val item = adapter.getItemAtPosition(position) as Book? ?: return

                val bookState = BookState(item.id, item.title, item.rating, item.read)

                val intent = Intent(applicationContext, EditActivity::class.java)
                state.addToIntent(intent)
                bookState.addToIntent(intent)
                startActivity(intent)
            }
        }
    }

    override fun onResume() {
        super.onResume()
        adapter.items = null
        adapter.notifyDataSetChanged()
    }
}
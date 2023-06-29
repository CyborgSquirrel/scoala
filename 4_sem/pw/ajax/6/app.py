import flask
import sqlite3
import json
import random
import contextlib
import typing
import itertools
import pathlib
import os
import os.path


DATABASE_PATH = "data.db"


with contextlib.closing(sqlite3.connect(DATABASE_PATH)) as connection:
    connection.executescript("""
        CREATE TABLE IF NOT EXISTS Laptop(
              name TEXT PRIMARY KEY
            , producer TEXT
            , processor TEXT
            , memory TEXT
            , storage_capacity TEXT
            , storage_type TEXT
            , video_card TEXT
        )
    """)
    
    if False:
        with connection:
            laptops = [
                ("MacBook Air", "Apple", "M1 chip", "8GB", "256GB", "SSD", "Integrated GPU"),
                ("XPS 13", "Dell", "11th Gen Intel Core i7", "16GB", "512GB", "SSD", "Intel Iris Xe Graphics"),
                ("ZenBook UX425", "Asus", "11th Gen Intel Core i7", "16GB", "512GB", "SSD", "Intel Iris Xe Graphics"),
                ("Surface Laptop 4", "Microsoft", "AMD Ryzen 7 4980U", "16GB", "512GB", "SSD", "AMD Radeon Graphics"),
                ("ThinkPad X1 Carbon", "Lenovo", "11th Gen Intel Core i7", "16GB", "512GB", "SSD", "Intel Iris Xe Graphics"),
                ("ENVY x360", "HP", "11th Gen Intel Core i7", "16GB", "512GB", "SSD", "Intel Iris Xe Graphics"),
                ("Gram 17", "LG", "11th Gen Intel Core i7", "16GB", "1TB", "SSD", "Intel Iris Xe Graphics"),
                ("ROG Zephyrus G15", "Asus", "AMD Ryzen 9 5900HS", "16GB", "1TB", "SSD", "NVIDIA GeForce RTX 3080"),
                ("Legion 5", "Lenovo", "AMD Ryzen 7 5800H", "16GB", "512GB", "SSD", "NVIDIA GeForce RTX 3060"),
                ("Blade 15 Base Model", "Razer", "10th Gen Intel Core i7", "16GB", "512GB", "SSD", "NVIDIA GeForce RTX 2060"),
                ("IdeaPad Gaming 3", "Lenovo", "AMD Ryzen 7 4800H", "8GB", "512GB", "SSD", "NVIDIA GeForce GTX 1650"),
                ("Pavilion Gaming 15", "HP", "11th Gen Intel Core i5", "8GB", "256GB", "SSD", "NVIDIA GeForce GTX 1650"),
                ("Nitro 5", "Acer", "AMD Ryzen 5 5600H", "8GB", "512GB", "SSD", "NVIDIA GeForce GTX 1650"),
                ("VivoBook S15", "Asus", "11th Gen Intel Core i7", "16GB", "1TB", "SSD", "Intel Iris Xe Graphics"),
                ("Swift 3", "Acer", "11th Gen Intel Core i7", "16GB", "1TB", "SSD", "Intel Iris Xe Graphics"),
                ("Chromebook Spin 713", "Acer", "Intel Core i5-10210U", "8GB", "128GB", "SSD", "Intel UHD Graphics"),
                ("Latitude 7410", "Dell", "10th Gen Intel Core i7", "16GB", "512GB", "SSD", "Intel UHD Graphics"),
                ("ProBook 450 G8", "HP", "11th Gen Intel Core i5", "8GB", "256GB", "SSD", "Intel UHD Graphics"),
                ("TUF Gaming F15", "Asus", "11th Gen Intel Core i5", "8GB", "512GB", "SSD", "NVIDIA GeForce GTX 1650"),
                ("Legion 7", "Lenovo", "11th Gen Intel Core i7", "16GB", "1TB", "SSD", "NVIDIA GeForce RTX 3070"),
                ("ROG Strix G17", "Asus", "AMD Ryzen 9 5900HX", "16GB", "1TB", "SSD", "NVIDIA GeForce RTX 3080"),
                ("Blade Pro 17", "Razer", "11th Gen Intel Core i7", "16GB", "1TB", "SSD", "NVIDIA GeForce RTX 3070"),
                ("Galaxy Book Flex2", "Samsung", "11th Gen Intel Core i7", "16GB", "512GB", "SSD", "Intel Iris Xe Graphics"),
                ("Spectre x360", "HP", "11th Gen Intel Core i7", "16GB", "1TB", "SSD", "Intel Iris Xe Graphics"),
                ("Prestige 14", "MSI", "11th Gen Intel Core i7", "16GB", "512GB", "SSD", "Intel Iris Xe Graphics"),
                ("HP 17", "HP", "Intel Core i5-1135G7", "8GB", "1TB", "HDD", "Intel Iris Xe Graphics"),
                ("Acer Aspire 5", "Acer", "AMD Ryzen 5 4500U", "8GB", "1TB", "HDD", "AMD Radeon Graphics"),
                ("Lenovo IdeaPad 3", "Lenovo", "AMD Ryzen 5 3500U", "8GB", "1TB", "HDD", "AMD Radeon Vega 8 Graphics"),
                ("Dell Inspiron 15", "Dell", "Intel Core i5-10210U", "8GB", "1TB", "HDD", "Intel UHD Graphics"),
                ("ASUS VivoBook 15", "ASUS", "Intel Core i3-1005G1", "4GB", "1TB", "HDD", "Intel UHD Graphics"),
            ]
            
            connection.executemany(
                "INSERT INTO Laptop (name, producer, processor, memory, storage_capacity, storage_type, video_card) VALUES (?, ?, ?, ?, ?, ?, ?)",
                laptops,
            )


app = flask.Flask(__name__)

@app.route("/request", methods=["POST"])
def request():
    data = json.loads(flask.request.data)

    with contextlib.closing(sqlite3.connect(DATABASE_PATH)) as connection:
        if "GetFilters" in data:
            columns = [
                { "table_name": "producer"        , "response_name": "producer"        },
                { "table_name": "processor"       , "response_name": "processor"       },
                { "table_name": "memory"          , "response_name": "memory"          },
                { "table_name": "storage_capacity", "response_name": "storageCapacity" },
                { "table_name": "storage_type"    , "response_name": "storageType"     },
                { "table_name": "video_card"      , "response_name": "videoCard"       },
            ]

            response = { }
            for column in columns:
                table_name = column["table_name"]
                query_str = f"SELECT DISTINCT {table_name} FROM Laptop"
                response[column["response_name"]] = list(connection.execute(query_str))

            return flask.jsonify(response)
        elif "GetLaptops" in data:
            query_filters = dict()
            
            query_filters["producer"]         = data["GetLaptops"]["producer"]
            query_filters["processor"]        = data["GetLaptops"]["processor"]
            query_filters["memory"]           = data["GetLaptops"]["memory"]
            query_filters["storage_capacity"] = data["GetLaptops"]["storageCapacity"]
            query_filters["storage_type"]     = data["GetLaptops"]["storageType"]
            query_filters["video_card"]       = data["GetLaptops"]["videoCard"]

            field_filters = []
            field_values = []
            for field, value in query_filters.items():
                if value is not None:
                    field_filters.append(f"{field} = ?")
                    field_values.append(value)

            field_values = tuple(field_values)
            
            if len(field_filters) > 0:
                filter_str = "WHERE " + " AND ".join(field_filters)
            else:
                filter_str = ""
            
            query_str = "SELECT name, producer, processor, memory, storage_capacity, storage_type, video_card FROM Laptop"
            if len(filter_str) > 0:
                query_str += " "
                query_str += filter_str
            
            laptops = list(connection.execute(query_str, field_values))
            response = [
                {
                    "name": laptop[0],
                    "producer": laptop[1],
                    "processor": laptop[2],
                    "memory": laptop[3],
                    "storageCapacity": laptop[4],
                    "storageType": laptop[5],
                    "videoCard": laptop[6],
                }
                for laptop in laptops
            ]
        
            return flask.jsonify(response)
        else:
            assert False

    return None

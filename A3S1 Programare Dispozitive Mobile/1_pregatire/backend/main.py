import argparse
import random
import dataclasses
import datetime
import hashlib
import json as jsonlib
import os
import pathlib
from http import HTTPStatus as status

import dacite
import flask
import flask_cors
import flask_jwt_extended as flask_jwt
import flask_socketio
import sqlalchemy
import sqlalchemy.orm

import db


@dataclasses.dataclass
class PostBook:
    read: bool
    title: str
    rating: int
    date_added: int
    lat: float
    lng: float


# global stuff
app = flask.Flask(__name__)
flask_cors.CORS(app)  # farewell, cors
socketio = flask_socketio.SocketIO(
    app,
    cors_allowed_origins="*",
)
socketio_sid_to_user_id = dict()


# Produsele sunt aduse de pe server prin
# http GET /product?page=n, paginat, cu maxim 10 produse per pagina. Raspunsul serverului este
# in formatul { total, page, products }, total - indicand numarul total al produselor,
# page - pagina curenta, products - produsele paginii curente.
@app.get("/product")
def get_product():
    page = flask.request.args.get("page")
    if page is None:
        return "", status.BAD_REQUEST
    try:
        page = int(page)
    except ValueError:
        return "", status.BAD_REQUEST

    # Randomly fail the request
    # if random.random() < 0.2:
    #     return "", status.BAD_REQUEST
    
    with sqlalchemy.orm.Session(engine) as session:
        query = (
            sqlalchemy.select(db.Product)
            .order_by(db.Product.code)
            .offset(page*10)
            .limit(10)
        )
        products = session.scalars(query)
        products = [product.to_dict() for product in products]

        total = session.scalar(sqlalchemy.select(sqlalchemy.func.count(db.Product.code)))

    return (
        dict(
            total=total,
            page=page,
            products=products,
        )
    )


@dataclasses.dataclass
class PostItem:
    product_code: int
    quantity: int


@app.post("/item")
def post_item():
    post_item = dacite.from_dict(PostItem, flask.request.json)
    with sqlalchemy.orm.Session(engine) as session:
        item = db.Item(
            product_code=post_item.product_code,
            quantity=post_item.quantity,
        )
        session.add(item)
        session.commit()
    return "", status.OK


@dataclasses.dataclass
class PostProduct:
    name: str


@app.post("/product")
def post_product():
    post_product = dacite.from_dict(PostProduct, flask.request.json)
    with sqlalchemy.orm.Session(engine) as session:
        product = db.Product(
            name=post_product.name,
        )
        session.add(product)
        session.commit()
    socketio.emit("products_changed")
    return "", status.OK


if __name__ == "__main__":
    data_dir = pathlib.Path("data")
    os.makedirs(data_dir, exist_ok=True)
    
    # database stuff
    data_path = data_dir / "data.db"
    # engine = sqlalchemy.create_engine(f"sqlite:///{data_path}")
    engine = sqlalchemy.create_engine("sqlite://")
    db.Base.metadata.create_all(engine)

    with sqlalchemy.orm.Session(engine) as session:
        for i in range(100):
            product = db.Product(name=f"Product {i}")
            session.add(product)
        session.commit()

    # cli args
    # argparser = argparse.ArgumentParser()
    # argparser.add_argument("config_path")
    # args = argparser.parse_args()

    # config
    # with open(args.config_path) as f:
    #     config = jsonlib.load(f)

    # jwt
    # app.config["JWT_SECRET_KEY"] = config["jwt_secret_key"]
    app.config["JWT_SECRET_KEY"] = "alabalaportocala"
    jwt = flask_jwt.JWTManager(app)
    
    # socketio
    socketio.run(app, host="0.0.0.0", port=3000, debug=True, use_reloader=False)

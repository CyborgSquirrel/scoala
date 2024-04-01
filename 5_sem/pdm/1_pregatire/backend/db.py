import datetime
import typing
from typing import List

from sqlalchemy import Boolean, DateTime, Float, ForeignKey, Integer
from sqlalchemy import \
    LargeBinary as Binary  # LargeBinary is a misleading name
from sqlalchemy import String
from sqlalchemy.orm import DeclarativeBase, Mapped, mapped_column, relationship


class Base(DeclarativeBase):
    pass


# Product
# code - numar intreg, name - sir de caractere
class Product(Base):
    __tablename__ = "Product"
    code: Mapped[int] = mapped_column(primary_key=True)
    name: Mapped[str] = mapped_column(String())

    def to_dict(self) -> typing.Any:
        return dict(
            code=self.code,
            name=self.name,
        )


# Item
# code - codul produsului, quantity - numar
class Item(Base):
    __tablename__ = "Item"
    code: Mapped[int] = mapped_column(primary_key=True)
    product_code: Mapped[int] = mapped_column(ForeignKey("Product.code"))
    quantity: Mapped[int] = mapped_column(Integer())


# class User(Base):
#     __tablename__ = "User"

#     id: Mapped[int] = mapped_column(primary_key=True)
#     name: Mapped[str] = mapped_column(String())
#     password_hash: Mapped[bytes] = mapped_column(Binary())
#     password_salt: Mapped[bytes] = mapped_column(Binary())

#     books: Mapped[List["Book"]] = relationship(back_populates="user")


# class Book(Base):
#     __tablename__ = "Book"

#     id: Mapped[int] = mapped_column(primary_key=True)
#     read: Mapped[bool] = mapped_column(Boolean())
#     title: Mapped[str] = mapped_column(String())
#     rating: Mapped[int] = mapped_column(Integer())
#     date_added: Mapped[datetime.datetime] = mapped_column(DateTime())
#     lat: Mapped[float] = mapped_column(Float())
#     lng: Mapped[float] = mapped_column(Float())

#     user_id: Mapped[int] = mapped_column(ForeignKey("User.id"))
#     user: Mapped["User"] = relationship(back_populates="books")

#     def to_jsonable(self) -> dict:
#         book = dict(
#             id=self.id,
#             read=self.read,
#             title=self.title,
#             rating=self.rating,
#             date_added=int(self.date_added.timestamp()),
#             lat=self.lat,
#             lng=self.lng,
#         )
#         return book

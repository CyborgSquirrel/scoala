import datetime
from typing import List

from sqlalchemy import Boolean, DateTime, ForeignKey, Integer
from sqlalchemy import \
    LargeBinary as Binary  # LargeBinary is a misleading name
from sqlalchemy import String
from sqlalchemy.orm import DeclarativeBase, Mapped, mapped_column, relationship


class Base(DeclarativeBase):
    pass


class User(Base):
    __tablename__ = "User"

    id: Mapped[int] = mapped_column(primary_key=True)
    name: Mapped[str] = mapped_column(String())
    password_hash: Mapped[bytes] = mapped_column(Binary())
    password_salt: Mapped[bytes] = mapped_column(Binary())

    books: Mapped[List["Book"]] = relationship(back_populates="user")


class Book(Base):
    __tablename__ = "Book"

    id: Mapped[int] = mapped_column(primary_key=True)
    read: Mapped[bool] = mapped_column(Boolean())
    title: Mapped[str] = mapped_column(String())
    rating: Mapped[int] = mapped_column(Integer())
    date_added: Mapped[datetime.datetime] = mapped_column(DateTime())

    user_id: Mapped[int] = mapped_column(ForeignKey("User.id"))
    user: Mapped["User"] = relationship(back_populates="books")

    def to_jsonable(self) -> dict:
        book = dict(
            id=self.id,
            read=self.read,
            title=self.title,
            rating=self.rating,
            date_added=int(self.date_added.timestamp()),
        )
        return book
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


# A message has the following props:
#   id - number,
#   text - string,
#   read - boolean flag indicating whether the message was read or not,
#   sender - string representing the name of the user who sent the message,
#   created - number representing the date when the message was created.
class Message(Base):
    __tablename__ = "Message"
    id: Mapped[int] = mapped_column(primary_key=True)
    text: Mapped[str] = mapped_column(String())
    read: Mapped[bool] = mapped_column(Boolean())
    sender: Mapped[str] = mapped_column(String())
    created: Mapped[int] = mapped_column(Integer())

    def to_dict(self) -> typing.Any:
        return dict(
            id=self.id,
            text=self.text,
            read=self.read,
            sender=self.sender,
            created=self.created,
        )

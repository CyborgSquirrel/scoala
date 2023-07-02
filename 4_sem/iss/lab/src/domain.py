import enum

import sqlalchemy
import sqlalchemy.orm


class Base(sqlalchemy.orm.DeclarativeBase):
    pass


class StareMembruEchipaj(enum.Enum):
    VIU = 1
    ELIMINAT = 2
    INVESTIGAT = 3


class MembruEchipaj(Base):
    __tablename__ = "MembruEchipaj"

    id: sqlalchemy.orm.Mapped[int] = sqlalchemy.orm.mapped_column(primary_key=True, autoincrement=True)
    nume: sqlalchemy.orm.Mapped[str] = sqlalchemy.orm.mapped_column(sqlalchemy.String(100))
    parola: sqlalchemy.orm.Mapped[str] = sqlalchemy.orm.mapped_column(sqlalchemy.String(100))
    stare: sqlalchemy.orm.Mapped[StareMembruEchipaj] = sqlalchemy.orm.mapped_column(sqlalchemy.Enum(StareMembruEchipaj))


class Impostor(MembruEchipaj):
    __tablename__ = "Impostor"

    membru_echipaj_id: sqlalchemy.orm.Mapped[int] = sqlalchemy.orm.mapped_column(
        sqlalchemy.ForeignKey("MembruEchipaj.id"),
        primary_key=True,
    )


class Coechipier(MembruEchipaj):
    __tablename__ = "Coechipier"

    membru_echipaj_id: sqlalchemy.orm.Mapped[int] = sqlalchemy.orm.mapped_column(
        sqlalchemy.ForeignKey("MembruEchipaj.id"),
        primary_key=True,
    )

    sarcini_completate: sqlalchemy.orm.Mapped[int]

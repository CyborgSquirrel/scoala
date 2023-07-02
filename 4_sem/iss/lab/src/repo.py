import domain
import sqlalchemy
import sqlalchemy.orm


class InstanceNotFoundException(Exception):
    pass



class RepoMembruEchipaj:
    def __init__(self, engine: sqlalchemy.Engine):
        self.__engine = engine

    def find(self, id: int) -> domain.MembruEchipaj:
        with sqlalchemy.orm.Session(self.__engine) as session:
            query = (
                sqlalchemy.Select(domain.MembruEchipaj)
                    .where(domain.MembruEchipaj.id == id)
            )
            membru_echipaj: MembruEchipaj = session.scalar(query)
            if membru_echipaj is None:
                raise InstanceNotFoundException()
            return membru_echipaj

    def update(self, new_membru_echipaj: domain.MembruEchipaj):
        with sqlalchemy.orm.Session(self.__engine) as session:
            statement = (
                sqlalchemy.Update(domain.MembruEchipaj)
                    .where(domain.MembruEchipaj.id == new_membru_echipaj.id)
                    .values(
                        nume=new_membru_echipaj.nume,
                        parola=new_membru_echipaj.parola,
                        stare=new_membru_echipaj.stare,
                    )
            )
            session.execute(statement)
            session.commit()

    def get_all(self) -> list[domain.MembruEchipaj]:
        with sqlalchemy.orm.Session(self.__engine) as session:
            query = (
                sqlalchemy.Select(domain.MembruEchipaj)
            )
            return list(session.scalars(query))


class RepoImpostor:
    def __init__(self, engine: sqlalchemy.Engine):
        self.__engine = engine

    def create(self, impostor: domain.Impostor):
        with sqlalchemy.orm.Session(self.__engine) as session:
            session.add(impostor)
            session.commit()
    
    def find(self, id: int) -> domain.Impostor:
        with sqlalchemy.orm.Session(self.__engine) as session:
            query = (
                sqlalchemy.Select(domain.Impostor)
                    .where(domain.Impostor.id == id)
            )
            impostor: Impostor = session.scalar(query)
            if impostor is None:
                raise InstanceNotFoundException()
            return impostor

    def update(self, new_impostor: domain.Impostor):
        with sqlalchemy.orm.Session(self.__engine) as session:
            statement = (
                sqlalchemy.Update(domain.MembruEchipaj)
                    .where(domain.MembruEchipaj.id == new_impostor.id)
                    .values(
                        nume=new_impostor.nume,
                        parola=new_impostor.parola,
                        stare=new_impostor.stare,
                    )
            )
            session.execute(statement)
            session.commit()

    def delete(self, id: int):
        with sqlalchemy.orm.Session(self.__engine) as session:
            statement = (
                sqlalchemy.Delete(domain.Impostor)
                    .where(domain.Impostor.id == id)
            )
            session.execute(statement)
            session.commit()

            statement = (
                sqlalchemy.Delete(domain.MembruEchipaj)
                    .where(domain.MembruEchipaj.id == id)
            )
            session.execute(statement)
            session.commit()

    def get_all(self) -> list[domain.Impostor]:
        with sqlalchemy.orm.Session(self.__engine) as session:
            query = (
                sqlalchemy.Select(domain.Impostor)
            )
            return list(session.scalars(query))


class RepoCoechpier:
    def __init__(self, engine: sqlalchemy.Engine):
        self.__engine = engine

    def create(self, coechipier: domain.Coechipier):
        with sqlalchemy.orm.Session(self.__engine) as session:
            session.add(coechipier)
            session.commit()
    
    def find(self, id: int) -> domain.Coechipier:
        with sqlalchemy.orm.Session(self.__engine) as session:
            query = (
                sqlalchemy.Select(domain.Coechipier)
                    .where(domain.Coechipier.id == id)
            )
            coechipier: Coechipier = session.scalar(query)
            if coechipier is None:
                raise InstanceNotFoundException()
            return coechipier

    def update(self, new_coechipier: domain.Coechipier):
        with sqlalchemy.orm.Session(self.__engine) as session:
            statement = (
                sqlalchemy.Update(domain.MembruEchipaj)
                    .where(domain.MembruEchipaj.id == new_coechipier.id)
                    .values(
                        nume=new_coechipier.nume,
                        parola=new_coechipier.parola,
                        stare=new_coechipier.stare,
                    )
            )
            session.execute(statement)
            statement = (
                sqlalchemy.Update(domain.Coechipier)
                    .where(domain.Coechipier.id == new_coechipier.id)
                    .values(
                        sarcini_completate=new_coechipier.sarcini_completate,
                    )
            )
            session.execute(statement)
            session.commit()

    def delete(self, id: int):
        with sqlalchemy.orm.Session(self.__engine) as session:
            statement = (
                sqlalchemy.Delete(domain.Coechipier)
                    .where(domain.Coechipier.id == id)
            )
            session.execute(statement)
            session.commit()

            statement = (
                sqlalchemy.Delete(domain.MembruEchipaj)
                    .where(domain.MembruEchipaj.id == id)
            )
            session.execute(statement)
            session.commit()

    def get_all(self) -> list[domain.Coechipier]:
        with sqlalchemy.orm.Session(self.__engine) as session:
            query = (
                sqlalchemy.Select(domain.Coechipier)
            )
            return list(session.scalars(query))

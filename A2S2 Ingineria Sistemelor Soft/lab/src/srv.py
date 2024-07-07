import domain
import typing
import sqlalchemy
import sqlalchemy.orm
import abc
import repo


class SrvException(Exception, metaclass=abc.ABCMeta):
    def to_string(self) -> str:
        pass


class NumeNevalidException(SrvException):
    def to_string(self) -> str:
        return "Numele nu este valid."


class ParolaNevalidaException(SrvException):
    def to_string(self) -> str:
        return "Parola nu este valida."


class AutoEliminareException(SrvException):
    def to_string(self) -> str:
        return "Ati incercat sa va auto-eliminati, ceea ce nu este permis."


class SrvApplication:
    def __init__(
        self,
        repo_membru_echipaj: repo.RepoMembruEchipaj,
        repo_impostor: repo.RepoImpostor,
        repo_coechipier: repo.RepoCoechpier,
    ):
        self.__repo_membru_echipaj = repo_membru_echipaj
        self.__repo_impostor = repo_impostor
        self.__repo_coechipier = repo_coechipier

        self.__on_membri_echipaj_stare_modified = []
        self.__on_membri_echipaj_sarcini_completate_modified = []

    def register_on_membri_echipaj_stare_modified(self, callback: typing.Callable[[], None]):
        self.__on_membri_echipaj_stare_modified.append(callback)

    def register_on_membri_echipaj_sarcini_completate_modified(self, callback: typing.Callable[[], None]):
        self.__on_membri_echipaj_sarcini_completate_modified.append(callback)
    
    def log_in(
        self,
        nume: str,
        parola: str,
    ) -> typing.Union[domain.Impostor, domain.Coechipier]:
        impostors = self.__repo_impostor.get_all()
        for impostor in impostors:
            if impostor.nume == nume:
                if impostor.parola != parola:
                    raise ParolaNevalidaException()
                return impostor
            
        coechipieri = self.__repo_coechipier.get_all()
        for coechipier in coechipieri:
            if coechipier.nume == nume:
                if coechipier.parola != parola:
                    raise ParolaNevalidaException()
                return coechipier

        raise NumeNevalidException()
    
    def elimina_membru(
        self,
        impostor_id: int,
        membru_id: int,
    ):
        if impostor_id == membru_id:
            raise AutoEliminareException()

        membru = self.__repo_membru_echipaj.find(membru_id)
        membru.stare = domain.StareMembruEchipaj.ELIMINAT
        self.__repo_membru_echipaj.update(membru)
        
        for callback in self.__on_membri_echipaj_stare_modified:
            callback()
    
    def investigheaza_corp(
        self,
        membru_echipaj_id: int,
        corp_id: int,
    ):
        corp = self.__repo_membru_echipaj.find(corp_id)
        corp.stare = domain.StareMembruEchipaj.INVESTIGAT
        self.__repo_membru_echipaj.update(corp)

        for callback in self.__on_membri_echipaj_stare_modified:
            callback()

    def completeaza_sarcina(
        self,
        coechpier_id: int,
    ):
        coechipier = self.__repo_coechipier.find(coechpier_id)
        coechipier.sarcini_completate += 1
        self.__repo_coechipier.update(coechipier)

        for callback in self.__on_membri_echipaj_sarcini_completate_modified:
            callback()

    def get_sarcini_completate(
        self,
        coechipier_id: int,
    ) -> int:
        coechipier = self.__repo_coechipier.find(coechipier_id)
        return coechipier.sarcini_completate
       
    
    def get_membri_echipaj_vii(self) -> list[domain.MembruEchipaj]:
        membri_echipaj = self.__repo_membru_echipaj.get_all()
        membri_echipaj = [
            membru_echipaj
            for membru_echipaj in membri_echipaj
            if membru_echipaj.stare == domain.StareMembruEchipaj.VIU
        ]
        return membri_echipaj

    def get_membri_echipaj_eliminati(self) -> list[domain.MembruEchipaj]:
        membri_echipaj = self.__repo_membru_echipaj.get_all()
        membri_echipaj = [
            membru_echipaj
            for membru_echipaj in membri_echipaj
            if membru_echipaj.stare == domain.StareMembruEchipaj.ELIMINAT
        ]
        return membri_echipaj

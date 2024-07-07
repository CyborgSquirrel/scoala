import abc


class Vehicle(abc.ABC):
    _basePrice: int

    def __init__(self, basePrice: int):
        if basePrice <= 0:
            raise ValueError("basePrice must be > 0")
        self._basePrice = basePrice

    @abc.abstractmethod
    def description(self) -> str:
        pass

    def getPrice(self) -> int:
        return self._basePrice


class Car(Vehicle):
    _model: str

    def __init__(self, basePrice: int, model: str):
        super().__init__(basePrice)
        if model is None or len(model) <= 0:
            raise ValueError("model must not be None or empty string")
        self._model = model

    def description(self) -> str:
        return self._model


class AutomaticCar(Car):
    _additionalPrice: int

    def __init__(self, basePrice: int, model: str, additionalPrice: int):
        super().__init__(basePrice, model)
        if additionalPrice <= 0:
            raise ValueError("additionalPrice must be > 0")
        self._additionalPrice = additionalPrice

    def description(self):
        return "Automatic car " + self._model

    def getPrice(self) -> int:
        return self._basePrice + self._additionalPrice


class CarWithParkingSensor(Car):
    _sensorType: str

    def __init__(self, basePrice: int, model: str, sensorType: str):
        super().__init__(basePrice, model)
        if sensorType is None or len(sensorType) <= 0:
            raise ValueError("sensorType must not be None or empty string")
        self._sensorType = sensorType

    def getPrice(self):
        return self._basePrice + 2500

    def description(self):
        return "Car with parking sensor " + self._sensorType + " " + self._model


def countUp(list_: list[Vehicle]) -> list[tuple[str, int]]:
    totals = dict()
    for vehicle in list_:
        if isinstance(vehicle, Car):
            # WHAT: How are you supposed to get the cars' models though?
            # - not all `Vehicle`s have a model, only `Car`s
            # - you can't define new methods, so you can't add a getModel()
            #
            # gg my friend

            model = vehicle._model
            if model not in totals:
                totals[model] = 0
            totals[model] += 1

    result = list(totals.items())
    return result


def goInsane(list_: list[Vehicle]):
    def first(vehicle: Vehicle) -> bool:
        return 1000 <= vehicle.getPrice() <= 2000
    
    for i in range(len(list_)):
        j = i
        while j >= 1 and first(list_[j]) and not first(list_[j-1]):
            list_[j], list_[j-1] = list_[j-1], list_[j]
            j -= 1


def whatAreWeLookingAt(list_: list[Vehicle]):
    for vehicle in list_:
        print(vehicle.getPrice(), vehicle.description())


def main():
    list_ = [
        Car(1800, "Audi"),
        AutomaticCar(1800, "Audi", 500),
        AutomaticCar(3000, "Mercedes", 650),
        CarWithParkingSensor(2500, "Opel", "parktron3000"),
        Car(1500, "Toyota"),
    ]

    theTotals = countUp(list_)
    print(theTotals)

    whatAreWeLookingAt(list_)
    print()
    goInsane(list_)
    whatAreWeLookingAt(list_)


if __name__ == "__main__":
    main()

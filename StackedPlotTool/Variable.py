import ROOT
class Variable:
    def __init__(self, name: str, numberOfEntries: int, histoPtr: ROOT.TH1)->None:
        self.name = name
        self.numberOfEntries = numberOfEntries
        self.histoPtr = histoPtr
        self.values = []
        self.eventWeight = 0.0
    
    def __cleanValues(self)->None:
        self.values.clear()
        self.eventWeight = 0.0
    
    def setValues(self, values: list, eventWeight)->None:
        self.__cleanValues()
        if len(values) != self.numberOfEntries:
            print(f'ERROR: Number of entries in {self.name} is not equal to {self.numberOfEntries}')
            exit(1)
        self.values = values
        self.eventWeight = eventWeight

    def fillHisto(self)->None:

        if len(self.values) != self.numberOfEntries:
            print(f'ERROR: Number of entries in {self.name} is not equal to {self.numberOfEntries}')
            exit(1)

        for value in self.values:
            self.histoPtr.Fill(value, self.eventWeight)
        
        self.__cleanValues()

    def namedAs(self, name: str) -> bool:
        """
        Checks if the variable is named as the given name.

        Args:
            name (str): The name to compare against.

        Returns:
            bool: True if the variable is named as the given name, False otherwise.
        """
        return self.name == name
    
    def __repr__(self) -> str:
        result = f'{self.name} with {self.numberOfEntries} entries'
        result += f'\n\tValues: {self.values} ; Values count: {len(self.values)}'
        return result
    
    def __str__(self) -> str:
        return self.__repr__()
    
    def __len__(self) -> int:
        return len(self.values)
    
    def __getitem__(self, index: int):
        return self.values[index]
    
    def __setitem__(self, index: int, value):
        self.values[index] = value

    def __delitem__(self, index: int):
        del self.values[index]

    def __iter__(self):
        return iter(self.values)
    
    def __next__(self):
        return next(self.values)

    def __contains__(self, value):
        return value in self.values
    
    def __add__(self, other):
        if isinstance(other, Varaible):
            return self.values + other.values
        return self.values + other
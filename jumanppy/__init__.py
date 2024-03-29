import ctypes
from os.path import dirname, join
from json import loads
from typing import List

model_path = join(dirname(__file__), "jumandic.jppmdl")
library_path = join(dirname(__file__), "libjumanppy.dylib")


class Morpheme:
    def __init__(self, json):
        self.surface = json['surface']
        self.pronunciation = json['pronunciation']
        self.baseForm = json['baseForm']
        self.pos = json['pos']
        self.subpos = json['subpos']
        self.conjForm = json['conjForm']
        self.conjType = json['conjType']
        self.reading = json['reading']
 
    def __repr__(self):
        return f"{self.surface}\t{self.pronunciation}\t{self.baseForm}\t{self.pos}\t{self.subpos}\t{self.conjForm}\t{self.conjType}\t{self.reading}"


libjumanppy = ctypes.CDLL(library_path)

libjumanppy.analyze.argtypes = [ctypes.c_char_p, ctypes.c_char_p]
libjumanppy.analyze.restype = ctypes.c_char_p


def analyze(text: str, model: str = model_path) -> List[Morpheme]:
    result = libjumanppy.analyze(model.encode('utf8'), text.encode('utf8'))
    morphemes = [Morpheme(morpheme) for morpheme in loads(result)]
    return morphemes


if __name__ == "__main__":
    print(model_path)
    print(analyze("相手の名前はよく分かりませんでした、すみません。"))

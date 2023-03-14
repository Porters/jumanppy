import ctypes
from os.path import relpath
from json import loads
from typing import List


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


libjumanppy = ctypes.CDLL(relpath("./jumanppy/libjumanppy.dylib"))

libjumanppy.analyze.argtypes = [ctypes.c_char_p, ctypes.c_char_p]
libjumanppy.analyze.restype = ctypes.c_char_p


def analyze(model: str, text: str) -> List[Morpheme]:
    result = libjumanppy.analyze(model, text)
    morphemes = [Morpheme(morpheme) for morpheme in loads(result)]
    return morphemes


if __name__ == "__main__":
    model_path = relpath("./jumanppy/jumandic.jppmdl")
    print(model_path)
    print(analyze(model_path.encode('utf8'), "相手の名前はよく分かりませんでした、すみません。".encode('utf8')))

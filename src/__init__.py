import ctypes
import os


class Morpheme(ctypes.Structure):
    _fields_ = [
        ("surface", ctypes.c_char_p),
        ("reading", ctypes.c_char_p),
        ("pos", ctypes.c_char_p),
        ("subpos", ctypes.c_char_p),
        ("conjForm", ctypes.c_char_p),
        ("conjType", ctypes.c_char_p),
        ("baseForm", ctypes.c_char_p),
        ("pronunciation", ctypes.c_char_p),
    ]

    def __repr__(self):
        return f'{self.surface} {self.reading} {self.pos} {self.subpos}'


libjumanppy = ctypes.CDLL(os.path.abspath("/Users/rav/repos/github/jumanppy/lib/libjumanppy.dylib"))

libjumanppy.analyze.argtypes = [ctypes.c_char_p, ctypes.c_char_p]
libjumanppy.analyze.restype = ctypes.POINTER(Morpheme)


def analyze(model: str, text: str):
    result = libjumanppy.analyze(model, text)
    print(result[:5])
    print("=========== OUTPUT ===========")
    # print(result.contents)
        

if __name__ == "__main__":
    print(analyze("/Users/rav/repos/github/jumanppy/jumandic.jppmdl".encode('utf8'), "日本語の形態素解析を行います。".encode('utf8')))

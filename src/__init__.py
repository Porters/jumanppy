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


libjumanppy = ctypes.CDLL(os.path.abspath("/Users/rav/repos/github/jumanppy/build/src/libjumanppy.so"))

analyze = libjumanppy.analyze
analyze.argtypes = [ctypes.c_char_p, ctypes.c_char_p]
analyze.restype = ctypes.POINTER(Morpheme)


if __name__ == "__main__":
    print(analyze("/Users/rav/repos/github/jumanppy/jumandic.jppmdl", "日本語の形態素解析を行います。"))

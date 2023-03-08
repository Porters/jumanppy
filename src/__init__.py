import ctypes
import os

# Load the shared library
libjumanpp = ctypes.CDLL(os.path.abspath("libjumanpp.so"))


# Define the ResultOutputter struct
class ResultOutputter(ctypes.Structure):
    _fields_ = [
        ("surface", ctypes.c_char_p),
        ("english", ctypes.c_char_p),
        ("resultFiller", ctypes.c_void_p),
        ("top1", ctypes.c_void_p),
    ]

    def initialize(self, ana):
        initialize = libjumanpp.ResultOutputter_initialize
        initialize.argtypes = [ctypes.c_void_p, ctypes.POINTER(ResultOutputter)]
        initialize.restype = ctypes.c_int
        return initialize(ana, ctypes.byref(self))

    def outputResult(self, ana):
        outputResult = libjumanpp.ResultOutputter_outputResult
        outputResult.argtypes = [ctypes.c_void_p, ctypes.POINTER(ResultOutputter)]
        outputResult.restype = ctypes.c_int
        return outputResult(ana, ctypes.byref(self))


# Define the dieOnError function
def dieOnError(status):
    if status != 0:
        raise Exception("Juman++ error: " + str(status))


# Define the main function
def analyze(text):
    # Load the Juman++ environment
    env = libjumanpp.JumanppEnv_new()
    dieOnError(
        libjumanpp.JumanppEnv_loadModel(env, ctypes.c_char_p(b"/path/to/model/dir"))
    )

    # Set the beam size
    libjumanpp.JumanppEnv_setBeamSize(env, 5)

    # Initialize the features
    dieOnError(libjumanpp.JumanppEnv_initFeatures(env, None))

    # Create an analyzer
    analyzer = libjumanpp.JumanppAnalyzer_new()
    dieOnError(libjumanpp.JumanppEnv_makeAnalyzer(env, analyzer))

    # Analyze the text
    result_outputter = ResultOutputter()
    dieOnError(result_outputter.initialize(analyzer))
    dieOnError(
        libjumanpp.JumanppAnalyzer_analyze(analyzer, ctypes.c_char_p(text.encode()))
    )
    result_outputter.outputResult(analyzer)

    # Clean up
    libjumanpp.JumanppAnalyzer_delete(analyzer)
    libjumanpp.JumanppEnv_delete(env)


if __name__ == "__main__":
    analyze("日本語の形態素解析を行います。")

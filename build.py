from os.path import isfile
from shutil import move, unpack_archive
from subprocess import Popen as shell

from requests import get
from setuptools import find_namespace_packages

target_dir: str = "jumanppy"


def makeJumanpp() -> None:
    print("makeJumanpp start")
    if not isfile(f"{target_dir}/libjumanppy.dylib"):
        build_dir = "tmp"
        shell(["mkdir", "-p", build_dir]).wait()
        shell(
            [
                "cmake",
                ".",
                "-B",
                build_dir,
                "-DCMAKE_BUILD_TYPE=Release",
                f"-DCMAKE_INSTALL_PREFIX={target_dir}",
            ]
        ).wait()
        shell(["make", "-C", build_dir, "install"]).wait()
        shell(["rm", "-rf", build_dir]).wait()
    print("makeJumanpp done")


def getModel() -> None:
    print("getModel start")
    build_dir = "tmp"
    archive_path = f"{build_dir}/jumanpp.tar.xz"
    archive_model_path = f"{build_dir}/jumandic-rnn.model"
    final_model_path = f"{target_dir}/jumandic.jppmdl"
    if not isfile(final_model_path):
        shell(["mkdir", "-p", build_dir]).wait()
        url = "https://github.com/ku-nlp/jumanpp-jumandic/releases/download/2020.08.12/jumandic-rnn.model.tar.xz"
        response = get(url)
        open(archive_path, "wb").write(response.content)
        unpack_archive(filename=archive_path, format="xztar", extract_dir=build_dir)
        move(archive_model_path, final_model_path)
        shell(["rm", "-rf", build_dir]).wait()
    print("getModel done")


def build(setup_kwargs: dict):
    print("Starting custom build.py")
    makeJumanpp()
    getModel()
    packages = find_namespace_packages()
    setup_kwargs.update(
        {
            "packages": packages,
            "exclude": ["dist", "build"],
            "include_package_data": True,
            "package_data": {
                "jumanppy": ["*.py", "libjumanppy.dylib", "jumandic.jppmdl"],
                "jumanpp": ["**"],
            },
        }
    )
    return setup_kwargs


if __name__ == "__main__":
    makeJumanpp()
    getModel()
    shell(["./jumanppy/jumanppy"]).wait()

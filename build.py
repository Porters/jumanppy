from subprocess import Popen as shell
from requests import get
from shutil import unpack_archive, move
from setuptools import find_namespace_packages

target_dir: str = "lib"
bin_dir: str = "bin"


def makeJumanpp() -> None:
    print("makeJumanpp start")
    build_dir = "tmp"
    shell(["mkdir", "-p", build_dir]).wait()
    shell(
        [
            "cmake",
            ".",
            "-B",
            build_dir,
            "-DCMAKE_BUILD_TYPE=Release",
            f"-DCMAKE_INSTALL_PREFIX={bin_dir}",
        ]
    ).wait()
    shell(["make", "-C", build_dir, "install"]).wait()
    shell(["rm", "-rf", build_dir]).wait()
    print("makeJumanpp done")


def getModel() -> None:
    print("getModel start")
    build_dir = "tmp"
    archive_path = f"{build_dir}/jumanpp.tar.xz"
    model_path = f"{build_dir}/jumanpp-2.0.0-rc3/model/jumandic.jppmdl"
    shell(["mkdir", "-p", build_dir]).wait()
    url = "https://github.com/ku-nlp/jumanpp/releases/download/v2.0.0-rc3/jumanpp-2.0.0-rc3.tar.xz"
    response = get(url)
    open(archive_path, "wb").write(response.content)
    unpack_archive(filename=archive_path, format="xztar", extract_dir=build_dir)
    move(model_path, f"{bin_dir}/jumandic.jppmdl")
    shell(["rm", "-rf", build_dir]).wait()
    print("getModel done")


def build(setup_kwargs: dict):
    print("Starting custom build.py")
    shell(["mkdir", "-p", target_dir]).wait()
    makeJumanpp()
    getModel()
    packages = find_namespace_packages()
    setup_kwargs.update(
        {
            "packages": packages,
            "exclude": ["dist", "build"],
            "include_package_data": True,
            "package_data": {
                "jumanppy": ["*.py"],
                "jumanpp": ["**"],
                bin_dir: ["**"],
            },
            "data_files": [
                (bin_dir, [f"{bin_dir}/libjumanppy.dylib" f"{bin_dir}/jumandic.jppmdl"])
            ],
        }
    )
    print(setup_kwargs)

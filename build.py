from subprocess import Popen as shell
from requests import get
from setuptools.command.build_ext import build_ext

build_dir = "tmp"
target_dir = "lib"


class MakeJumanpp(build_ext):
    def run(self) -> None:
        shell(f"mkdir -p {build_dir}").wait()
        shell(
            f"cmake . -B {build_dir} -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX={target_dir}",
            shell=True,
        ).wait()
        shell(f"make -C {build_dir} install", shell=True).wait()
        shell(f"rm -rf {build_dir}").wait()
        super().run()


class GetModel(build_ext):
    def run(self) -> None:
        url = "https://jumanppy.s3.ap-northeast-1.amazonaws.com/jumandic.jppmdl"
        response = get(url)
        open(f"{target_dir}/jumandicd.jppmdl", "wb").write(response.content)
        super().run()


def build(setup_kwargs):
    setup_kwargs.update(
        {
            "cmdclass": {
                "make_jumanpp": MakeJumanpp,
                "get_model": GetModel,
            }
        }
    )

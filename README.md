# jumanppy

jumanppy is a package including jumanpp. No additional installation is needed.

## Local development

```bash
git submodule init
git submodule update
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/Users/rav/repos/github/jumanppy/lib
make install
poetry install
```
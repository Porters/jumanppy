# jumanppy WORK IN PROGRESS

## Description

jumanppy is a package including jumanpp. No additional installation is needed.

## Local development

Get jumandic.jppmdl from a archive of a release of jumanpp

```bash
git submodule init
git submodule update
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/Users/rav/repos/github/jumanppy/lib
make install
poetry install
```

## Current state

Tokenization does not work as expected:
```
相手 名詞
の 助動詞
名 接頭辞
前 接尾辞
は 助詞
よ 動詞
く 接尾辞
分 動詞
か 動詞
りま 名詞
せ 接尾辞
ん 助動詞
で 動詞
し 接尾辞
た 動詞
、 特殊
す 動詞
み 接尾辞
ま 動詞
せ 接尾辞
ん 助動詞
。 特殊
```
Morpheme created byt not added to vector
Python layer not tested
Paths are hardcoded
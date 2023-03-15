# jumanppy

## Description

jumanppy is a package including jumanpp. No additional installation is needed. Package too big to be uploaded to pypi (about 340 MB).

## Local development


```bash
git submodule init
git submodule update
poetry build
```

`./jumanppy/jumanppy` allows to test the library.

## Data example

### Input

相手の名前はよく分かりませんでした、すみません。

### Output

```json
[
    {
        "baseForm": "相手",
        "conjForm": "",
        "conjType": "",
        "pos": "名詞",
        "pronunciation": "相手",
        "reading": "あいて",
        "subpos": "普通名詞",
        "surface": "相手"
    },
    {
        "baseForm": "の",
        "conjForm": "",
        "conjType": "",
        "pos": "助詞",
        "pronunciation": "の",
        "reading": "の",
        "subpos": "接続助詞",
        "surface": "の"
    },
    {
        "baseForm": "名前",
        "conjForm": "",
        "conjType": "",
        "pos": "名詞",
        "pronunciation": "名前",
        "reading": "なまえ",
        "subpos": "普通名詞",
        "surface": "名前"
    },
    {
        "baseForm": "は",
        "conjForm": "",
        "conjType": "",
        "pos": "助詞",
        "pronunciation": "は",
        "reading": "は",
        "subpos": "副助詞",
        "surface": "は"
    },
    {
        "baseForm": "よい",
        "conjForm": "基本連用形",
        "conjType": "イ形容詞アウオ段",
        "pos": "形容詞",
        "pronunciation": "よく",
        "reading": "よく",
        "subpos": "",
        "surface": "よく"
    },
    {
        "baseForm": "分かる",
        "conjForm": "基本連用形",
        "conjType": "子音動詞ラ行",
        "pos": "動詞",
        "pronunciation": "分かり",
        "reading": "わかり",
        "subpos": "",
        "surface": "分かり"
    },
    {
        "baseForm": "ます",
        "conjForm": "未然形",
        "conjType": "動詞性接尾辞ます型",
        "pos": "接尾辞",
        "pronunciation": "ませ",
        "reading": "ませ",
        "subpos": "動詞性接尾辞",
        "surface": "ませ"
    },
    {
        "baseForm": "ぬ",
        "conjForm": "音便基本形",
        "conjType": "助動詞ぬ型",
        "pos": "助動詞",
        "pronunciation": "ん",
        "reading": "ん",
        "subpos": "",
        "surface": "ん"
    },
    {
        "baseForm": "だ",
        "conjForm": "デス列タ形",
        "conjType": "判定詞",
        "pos": "判定詞",
        "pronunciation": "でした",
        "reading": "でした",
        "subpos": "",
        "surface": "でした"
    },
    {
        "baseForm": "、",
        "conjForm": "",
        "conjType": "",
        "pos": "特殊",
        "pronunciation": "、",
        "reading": "、",
        "subpos": "読点",
        "surface": "、"
    },
    {
        "baseForm": "すみません",
        "conjForm": "",
        "conjType": "",
        "pos": "感動詞",
        "pronunciation": "すみません",
        "reading": "すみません",
        "subpos": "",
        "surface": "すみません"
    },
    {
        "baseForm": "。",
        "conjForm": "",
        "conjType": "",
        "pos": "特殊",
        "pronunciation": "。",
        "reading": "。",
        "subpos": "句点",
        "surface": "。"
    }
]
```
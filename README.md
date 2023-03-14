# jumanppy WORK IN PROGRESS

## Description

jumanppy is a package including jumanpp. No additional installation is needed.

## Local development


```bash
git submodule init
git submodule update
poetry build
```

`jumanppy/jumanppy` allows to test the library.

## Current state

Tokenization does not work as expected when running `./jumanppy` from the jumanppy folder.

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
    "baseForm": "のだ",
    "conjForm": "語幹",
    "conjType": "ナ形容詞",
    "pos": "助動詞",
    "pronunciation": "の",
    "reading": "の",
    "subpos": "",
    "surface": "の"
  },
  {
    "baseForm": "名",
    "conjForm": "",
    "conjType": "",
    "pos": "接頭辞",
    "pronunciation": "名",
    "reading": "めい",
    "subpos": "名詞接頭辞",
    "surface": "名"
  },
  {
    "baseForm": "前",
    "conjForm": "",
    "conjType": "",
    "pos": "接尾辞",
    "pronunciation": "前",
    "reading": "まえ",
    "subpos": "名詞性名詞接尾辞",
    "surface": "前"
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
    "baseForm": "よす",
    "conjForm": "語幹",
    "conjType": "子音動詞サ行",
    "pos": "動詞",
    "pronunciation": "よ",
    "reading": "よ",
    "subpos": "",
    "surface": "よ"
  },
  {
    "baseForm": "く",
    "conjForm": "基本形",
    "conjType": "子音動詞カ行",
    "pos": "接尾辞",
    "pronunciation": "く",
    "reading": "く",
    "subpos": "動詞性接尾辞",
    "surface": "く"
  },
  {
    "baseForm": "分る",
    "conjForm": "語幹",
    "conjType": "子音動詞ラ行",
    "pos": "動詞",
    "pronunciation": "分",
    "reading": "分",
    "subpos": "",
    "surface": "分"
  },
  {
    "baseForm": "かう",
    "conjForm": "語幹",
    "conjType": "子音動詞ワ行",
    "pos": "動詞",
    "pronunciation": "か",
    "reading": "か",
    "subpos": "",
    "surface": "か"
  },
  {
    "baseForm": "りま",
    "conjForm": "",
    "conjType": "",
    "pos": "名詞",
    "pronunciation": "りま",
    "reading": "りま",
    "subpos": "人名",
    "surface": "りま"
  },
  {
    "baseForm": "する",
    "conjForm": "文語未然形",
    "conjType": "サ変動詞",
    "pos": "接尾辞",
    "pronunciation": "せ",
    "reading": "せ",
    "subpos": "動詞性接尾辞",
    "surface": "せ"
  },
  {
    "baseForm": "んだ",
    "conjForm": "語幹",
    "conjType": "ナ形容詞",
    "pos": "助動詞",
    "pronunciation": "ん",
    "reading": "ん",
    "subpos": "",
    "surface": "ん"
  },
  {
    "baseForm": "でる",
    "conjForm": "語幹",
    "conjType": "母音動詞",
    "pos": "動詞",
    "pronunciation": "で",
    "reading": "で",
    "subpos": "",
    "surface": "で"
  },
  {
    "baseForm": "する",
    "conjForm": "タ接連用形",
    "conjType": "サ変動詞",
    "pos": "接尾辞",
    "pronunciation": "し",
    "reading": "し",
    "subpos": "動詞性接尾辞",
    "surface": "し"
  },
  {
    "baseForm": "たつ",
    "conjForm": "語幹",
    "conjType": "子音動詞タ行",
    "pos": "動詞",
    "pronunciation": "た",
    "reading": "た",
    "subpos": "",
    "surface": "た"
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
    "baseForm": "すい",
    "conjForm": "語幹",
    "conjType": "イ形容詞アウオ段",
    "pos": "形容詞",
    "pronunciation": "す",
    "reading": "す",
    "subpos": "",
    "surface": "す"
  },
  {
    "baseForm": "みる",
    "conjForm": "未然形",
    "conjType": "母音動詞",
    "pos": "動詞",
    "pronunciation": "み",
    "reading": "み",
    "subpos": "",
    "surface": "み"
  },
  {
    "baseForm": "まく",
    "conjForm": "語幹",
    "conjType": "子音動詞カ行",
    "pos": "動詞",
    "pronunciation": "ま",
    "reading": "ま",
    "subpos": "",
    "surface": "ま"
  },
  {
    "baseForm": "せ",
    "conjForm": "",
    "conjType": "",
    "pos": "接尾辞",
    "pronunciation": "せ",
    "reading": "せ",
    "subpos": "名詞性名詞接尾辞",
    "surface": "せ"
  },
  {
    "baseForm": "んだ",
    "conjForm": "語幹",
    "conjType": "ナ形容詞",
    "pos": "助動詞",
    "pronunciation": "ん",
    "reading": "ん",
    "subpos": "",
    "surface": "ん"
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
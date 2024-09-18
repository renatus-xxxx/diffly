[English](README.md) / [Japanese](README.ja.md)

[![windows](https://github.com/renatus-xxxx/diffly/workflows/windows/badge.svg)](https://github.com/renatus-xxxx/diffly/actions?query=workflow%3Awindows)
[![macos](https://github.com/renatus-xxxx/diffly/workflows/macos/badge.svg)](https://github.com/renatus-xxxx/diffly/actions?query=workflow%3Amacos)
[![ubuntu](https://github.com/renatus-xxxx/diffly/workflows/ubuntu/badge.svg)](https://github.com/renatus-xxxx/diffly/actions?query=workflow%3Aubuntu)

<img src="https://raw.githubusercontent.com/renatus-xxxx/diffly/main/images/tether.png" title="tether" />

# diffly

**diffly** は、二つのテキストファイルを比較し、わかりやすい形式で diff を表示するシンプルで軽量なコマンドライン差分ツールです。

## 特徴

- 二つのテキストファイルを行ごとに比較
- 差分を side-by-side で表示
- `!`, `+`, `-` 記号を使った直感的な差分表示
- 行番号付きの出力で差分箇所を簡単に把握
- コマンドラインオプションで表示幅をカスタマイズ可能

## 使用法
```bash
./diffly <file1> <file2> [--width <number>]
```

- `<file1>`: 比較する最初のファイルのパス
- `<file2>`: 比較する2番目のファイルのパス
- --width <number> または -w <number>: (任意) 表示する行の幅（文字数）を指定。デフォルトは80文字。

## 例
```bash
./diffly original.txt modified.txt --width 40
```
## 出力例

```
   1   #include <stdio.h>              |    1   #include <stdio.h>             
   3 ! int main(int argc, char* arg... |    3 ! int main(argc, argv)           
   4 !   printf("Hello! ANSI-C worl... |    4 ! int argc;                      
                                       |    5 + char* argv[];                  
                                       |    6 + {                              
                                       |    7 +   printf("Hello! K&R-C world");
   5   }                               |    8   }                              
```

## ダウンロード
- [webmsxで試す](https://webmsx.org/?MACHINE=MSXTRJ&DISKA_URL=https://raw.githubusercontent.com/renatus-xxxx/diffly/main/bin/DIFFLY.DSK&FAST_BOOT)
- [.DSK イメージ(DOS for MSX v0.16 Gaku)](https://raw.githubusercontent.com/renatus-xxxx/diffly/main/bin/DIFFLY.DSK)
- [DIFFLY.COM](https://raw.githubusercontent.com/renatus-xxxx/diffly/main/bin/DIFFLY.COM)
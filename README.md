[English](README.md) / [Japanese](README.ja.md)

[![windows](https://github.com/renatus-xxxx/diffly/workflows/windows/badge.svg)](https://github.com/renatus-xxxx/diffly/actions?query=workflow%3Awindows)
[![macos](https://github.com/renatus-xxxx/diffly/workflows/macos/badge.svg)](https://github.com/renatus-xxxx/diffly/actions?query=workflow%3Amacos)
[![ubuntu](https://github.com/renatus-xxxx/diffly/workflows/ubuntu/badge.svg)](https://github.com/renatus-xxxx/diffly/actions?query=workflow%3Aubuntu)

<img src="https://raw.githubusercontent.com/renatus-xxxx/diffly/main/images/tether.png" title="tether" />

# diffly

**diffly** is a simple and lightweight command-line diff tool that compares two text files and displays the differences in an easy-to-understand format.


## Features

- Compare two text files line by line.
- Display differences side by side.
- Intuitive representation of differences using `!`, `+`, and `-` symbols
- Line-numbered output for easy location of differences
- Customize display width using command-line options.

## Usage
```bash
./diffly <file1> <file2> [--width <number>]
```

- `<file1>`: Path to the first file to compare.
- `<file2>`: Path to the second file to compare.
- --width <number> or -w <number>: (Optional) Specify the number of characters per line for display. Default width is 80.

## Example
```bash
./diffly original.txt modified.txt --width 40
```
## Output Example

```
   1   #include <stdio.h>              |    1   #include <stdio.h>             
   3 ! int main(int argc, char* arg... |    3 ! int main(argc, argv)           
   4 !   printf("Hello! ANSI-C worl... |    4 ! int argc;                      
                                       |    5 + char* argv[];                  
                                       |    6 + {                              
                                       |    7 +   printf("Hello! K&R-C world");
   5   }                               |    8   }                              
```

## Download
- [try on webmsx](https://webmsx.org/?MACHINE=MSXTRJ&DISKA_URL=https://raw.githubusercontent.com/renatus-xxxx/diffly/main/bin/DIFFLY.DSK&FAST_BOOT)
- [.DSK image(DOS for MSX v0.16 Gaku)](https://raw.githubusercontent.com/renatus-xxxx/diffly/main/bin/DIFFLY.DSK)
- [DIFFLY.COM](https://raw.githubusercontent.com/renatus-xxxx/diffly/main/bin/DIFFLY.COM)
# QREnconsole

QREnconsole is a CLI tool to display QR code in terminal.

## Prerequisite

* [libqrencode](https://github.com/fukuchi/libqrencode) >= 4.1.0
* Unix-like OS or derivatives
* C++ compiler you like (C++11 or later should be supported)

## Build and install

Linux

```shell
make
PREFIX=$HOME make install
```

macOS

```shell
c++ main.cpp -Wall -o qrenconsole
PREFIX=$HOME/local make install
```

## Usage

```shell
echo http://hoge.example.com | qrenconsole
{
  echo rsync://srv.some.example.org 
  echo words are separately converted
} | qrenconsole
```

## Author

Nomura Suzume <Suzume315[att]g00.g1e.org>
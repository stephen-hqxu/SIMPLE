<h1 align="center"> SIMPLE </h1>
<p align="center"> Smart INI Manager and Parser Lite Edition </p>

# About
SIMPLE is a light weight INI import and export library writen in C++ 17.

It allow user to parse INI file from their system with minimum efforts.
Currently it supports:
- No parsing comment
- Sectionless properties

In the future those features may be added:
- Case sensitivity
- Nested sections
- Output other data types other than string

## Performance
Load configurations will be stored in C++ `unordered_map`, properties can be search with a string

# User Guide

## Prerequisites

- Visual Studio 2019

> I will add supports for complication on Linux environment in the future.

## How to install
1. Simply clone our project repo
```sh
git clone https://github.com/stephen-hqxu/SIMPLE/
```
2. Open the solution with Visual Studio 2019
3. Select `Debug` or `Release` configuration depends on your need.
4. Hit `F7` to compile.
5. Find the static and dynamic library file in the output folder.
6. Include the static library into your project, copy the dynamic library to your executable directory.
7. And enjoy :stuck_out_tongue:

## Documatations :open_book:
The header file are clearly documented. I will consider adding separate document page in the future.

# Road Map
See [release note](https://github.com/stephen-hqxu/SIMPLE/releases) for a list of proposed features.

# License
Distributed under the MIT License. See `LICENSE` for more information.

# Contact
Stephen Xu - stephen.hqxu@gmail.com
Project Link: [Click Me](https://github.com/stephen-hqxu/SIMPLE)

# Acknowledgement
[README template](https://github.com/othneildrew/Best-README-Template)
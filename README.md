# osu-tournament-editor

A light-weight osu! tournament configuration editor written in C++, using [Qt 6](https://www.qt.io).

> [!NOTE]
> This project is still working in progress.
> Feature requests are welcome!

## Features

- Lightweight, no more dependency except Qt runtime environment needed
- Flexible multiple tab editing
- Simple and elegant interface

## Documentation

The help documentation would be placed in the [project wiki](https://github.com/CloneWith/osu-tournament-editor/wiki)
after most features of this project are implemented.

## Build

This project is tested on Windows and Linux (precisely **Arch Linux**).

You need to set the Qt development environment up to build this project from source code.

After that, run `cmake` first to configure the project:

```shell
# "build" refers to the build directory and can be replaced with another name by yourself
cmake . -B build
```

Then, inside the build directory, use `make` to build the project:

```shell
cd build
make
```

Wait for the build progress to complete, and the binary executable should be ready under this directory.

### Packaging on Windows

Linux builds would absolutely work as long as you have installed required runtime libraries, and you can share
the binary executable directly. On Windows platforms, you need to bundle dependency DLL files with the binary.

A recommended solution is to use the `windeployqt` utility provided by Qt:

```pwsh
<path-to-your-qt-dir>/<version-num>/<compiler>/bin/windeployqt.exe <binary-file>
```

...where `<binary-file>` refers to the output executable in [the step above](#build).

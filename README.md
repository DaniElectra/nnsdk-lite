# nnsdk-lite

This is an attempt at reverse-engineering the Nintendo SDK that is used inside Nintendo 3DS applications. However, this scope may expand to Wii U support (e.g. the RPLs) as some concepts are similar.

**NOTE: This project aims to provide a reference of what the SDK does, and it will probably not generate byte-matching code. That effort must be done in a case by case basis, considering that different versions of the SDK will have slight differences.**

There are some sections of code which have some uncertainties about what the original code was of how it was named. Those sections will have an `UNOFFICIAL` comment explaining what's missing.

## Building

This code hasn't been tested on hardware, but you can build it using the CMake version for the 3DS from devkitPro:

```sh
$ /opt/devkitpro/portlibs/3ds/bin/arm-none-eabi-cmake -B build
$ cd build
$ make
```

## Credits

Various sources have been used for this project:

- [libctru](https://github.com/devkitPro/libctru) and [wut](https://github.com/devkitPro/wut) for various code snippets
- [nnsdk](https://github.com/3dsdecomp/nnsdk) and [auto_nnsdk](https://github.com/gamestabled/auto_nnsdk) for various references
- [3dbrew](https://3dbrew.org) for being a valuable source of information

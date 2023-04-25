# patxio's fork of dwmstatus
## Description

Parsing systeminfo from files and commands' stdout, and hooking it into the root window of X11 via xcb. This status bar is most relavent to laptop users for DWM, and shows you the minimal info about system info. 

Minimal Output:
```cpp
/* current processs, ram free, charging, time */
│ vi │ 4(6540)GiB | +100% │ Thu 10/29  4:20
/* current processs, ram free, discharging, time */
│ vi │ 4(6540)GiB | -99% │ Thu 10/29  4:20
```
## Requirements
 - c compiler (Both GCC and Clang recommanded)
 - [xcb-util](https://xcb.freedesktop.org/) [For exporting status bar to root X11 window]
 - submodule [csysteminfo](https://github.com/worthless443/csysteminfo)

## Download
```bash
$ git clone -b semiworks https://github.com/worthless443/patxio_dwmstatus.git
$ cd patxio_dwmstatus
$ git submodule update --init
```

## Installation
Installation using **make**:
```bash
$ cd patxio_dwmstatus/src
$ make
```
## Running
```
$ ./dwmstatus_xcb  # for outputting to X11 root window
```

## Configuration
All configurations are done through `config.def.h`/`config.h`
to keep the program simple and fast(?).
Note: some functions may be commented from my usages.
Uncomment to use them.

## Features
 - Displays date, uptime, battery percentage, charging info
 - Displays the most recent process launched from the terminal

# dwmstatus
## Description
A simple, customizable status bar for Dynamic Window Manager(dwm), written in C.

Exports status bar to X11 root window via xcb instead of xlib

Output:
```
/* charging */
<---> │ 0.8GHz │ 36°C │ [91%+] │ 0:23 │ Thu 10/29  4:20
/* discharging */
<---> │ 0.8GHz │ 36°C │ [54%] │ 0:23 │ Thu 10/29  4:20
/* AC power */
<---> │ 0.8GHz │ 36°C │ [AC] │ 0:23 │ Thu 10/29  4:20
```

## Requirements
 - c compiler
 - [libxcb](https://xcb.freedesktop.org/) [For exporting status bar to root X11 window]
 - Kernel options:
    - CONFIG_PROC_FS: /proc file system support [For audio info]
   - CONFIG_SYSFS: sysfs file system support [Where most information will be parsed from]
   - CONFIG_THERMAL_HWMON: Expose thermal sensors as hwmon device [For getting cpu temps]

## Installation
First, download the source using either HTTP or SSH:
```
$ git clone https://gitlab.com/Kamiyaa/ruiji.git
$ git clone git@gitlab.com:Kamiyaa/ruiji.git
```
Then install using **make**:
```
$ cd dwmstatus/src
$ make
# make install
```
Alternatively, you can install using **meson**:
```
$ cd dwmstatus
$ meson build
$ ninja -C build
# ninja -C build install
```

## Running
```
dwmstatus_std  # for outputting to stdout
dwmstatus_xcb  # for outputting to X11 root window
```

## Configuration
All configurations are done through config.def.h/config.h
to keep the program simple and fast(?).
Note: some functions may be commented from my usages.
Uncomment to use them.

## Features
 - Displays date, uptime, battery percentage
 - Displays a single cpu's frequency and temperature
 - Displays network connections
   - only if connected to access point, not internet access

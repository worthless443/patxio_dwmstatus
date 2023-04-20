# compiler and linker
CC = clang
MEMPATH=../csysteminfo/
GIMPL_PATH=../glib_impl

NOFLAGS=-Wno-unused-command-line-argument -Wno-format-invalid-specifier
# flags
CFLAGS = -ggdb3 -Os -Wall -Wno-unused-variable -march=native -fno-stack-protector -D_GNU_SOURCE -I./ -I${MEMPATH} -L${MEMPATH} -L${GIMPL_PATH} -I/usr/include/glib-2.0/ -I /usr/lib/glib-2.0/include/ -I/usr/include/gdk-pixbuf-2.0  ${NOFLAGS}

# X11 export support
DEP_XCB = `pkg-config --cflags --libs xcb xcb-atom`

# output volume support
DEP_ALSA = `pkg-config --cflags --libs alsa`

LIBS = ${DEP_XCB} ${DEP_ALSA} -lmst -lnotify -lgimpl

PREFIX=/usr/local

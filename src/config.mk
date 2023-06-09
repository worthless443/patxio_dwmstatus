# compiler and linker
CC = gcc
MEMPATH=../csysteminfo/
GIMPL_PATH=../glib_impl

NOFLAGS=-Wno-unused-command-line-argument -Wno-format-invalid-specifier -Wformat=0
SANITIZER=-fsanitize=undefined,alignment
# flags
CFLAGS = -ggdb3  -O3 -Wall -Wno-unused-variable -march=native -fno-stack-protector -D_GNU_SOURCE -I./ -I${MEMPATH} -L${MEMPATH} -L${GIMPL_PATH} -I/usr/include/glib-2.0/ -I /usr/lib/glib-2.0/include/ -I/usr/include/gdk-pixbuf-2.0  ${NOFLAGS} ${SANITIZER}

# X11 export support
DEP_XCB = `pkg-config --cflags --libs xcb xcb-atom`

# output volume support
DEP_ALSA = `pkg-config --cflags --libs alsa`

LIBS = ${DEP_XCB} ${DEP_ALSA} -lmst -lnotify -lgimpl

PREFIX=/usr/local

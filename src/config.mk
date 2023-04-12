# compiler and linker
CC = cc
MEMPATH=/home/aissy/c_cpp/memused

# flags
CFLAGS = -ggdb3 -Os -Wall -Wno-unused-variable -march=native -fno-stack-protector -D_GNU_SOURCE -I./ -I${MEMPATH} -L${MEMPATH} -I/usr/include/glib-2.0/ -I /usr/lib/glib-2.0/include/ -I/usr/include/gdk-pixbuf-2.0

# X11 export support
DEP_XCB = `pkg-config --cflags --libs xcb xcb-atom`

# output volume support
DEP_ALSA = `pkg-config --cflags --libs alsa`

LIBS = ${DEP_XCB} ${DEP_ALSA} -lmst -lnotify

PREFIX=/usr/local

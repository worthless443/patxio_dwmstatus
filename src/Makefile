# Makefile

include config.mk
export

all: getdeps dwmstatus_xcb 

options:

	@echo "    CC = ${CC}"
	@echo "CFLAGS = ${CFLAGS}"
	@echo "  LIBS = ${LIBS}"

config.h: config.def.h

	@echo "cp config.def.h -> config.h"
	cp config.def.h config.h
getdeps:
	make -C ../glib_impl
	make -C ../csysteminfo
memused.o: 
	gcc -c ${CFLAGS} ${MEMPATH}/memused.c 
dwmstatus.o: dwmstatus.c dwmstatus.h config.h
	${CC} ${CFLAGS} -c dwmstatus.c

dwmstatus_xcb.o: dwmstatus.o dwmstatus_xcb.c
	${CC} ${CFLAGS} -c dwmstatus_xcb.c

dwmstatus_xcb: dwmstatus.o dwmstatus_xcb.o #memused.o
	${CC} ${CFLAGS} $^ -o $@ ${LIBS}

dwmstatus_std.o: dwmstatus.o dwmstatus_std.c
	${CC} ${CFLAGS} -c dwmstatus_std.c

dwmstatus_std: dwmstatus.o dwmstatus_std.o
	${CC} ${CFLAGS} $@.o dwmstatus.o -o $@ ${LIBS}

install:
	cp -f dwmstatus_std ${PREFIX}/bin/dwmstatus_std
	cp -f dwmstatus_xcb ${PREFIX}/bin/dwmstatus_xcb

clean:
	make -C ${MEMPATH} clean
	make -C ${GIMPL_PATH} clean
	rm -f *.o dwmstatus_std dwmstatus_xcb 

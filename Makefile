# Makefile


.PHONY: all install clean

CC 	    ?= gcc
CFLAGS  ?= -fPIC -Wall -Wextra -O2 -g
PREFIX  ?= /usr
LDFLAGS ?= -shared

LIB_NAME 		:= mrfp
TARGET			:= lib$(LIB_NAME).so
TARGET_HEADER 	:= src/$(LIB_NAME).h
SOURCES 		!= find . -type f -name '*.c'
OBJS 			:= $(SOURCES:.c=.o)
DEPS			:= $(OBJS:.o=.d)

all: ${TARGET}

$(TARGET): $(OBJS)
	$(CC) ${LDFLAGS} -o $@ $^

$(DEPS):%.d:%.c
	@$(CC) $(CFLAGS) -MM $< >$@

include $(DEPS)

clean:
	@printf "\033[1mCLEAN\033[0m\n"
	@rm -rf ${OBJS} ${DEPS} ${TARGET}

install: ${TARGET}
	install -d $(DESTDIR)$(PREFIX)/lib/
	install -m 644 ${TARGET} $(DESTDIR)${PREFIX}/lib/
	install -d $(DESTDIR)$(PREFIX)/include/
	install -m 644 ${TARGET_HEADER} $(DESTDIR)$(PREFIX)/include/
	ldconfig

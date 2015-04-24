MAKEFLAGS+=-rR
CC:=clang
CFLAGS:=-std=c11 -O2 -D_POSIX_C_SOURCE=200809L -D_XOPEN_SOURCE=700 -Werror -Weverything -Wno-parentheses -Wno-missing-prototypes -Wno-sign-conversion
all: cat
%: %.c Makefile
	@echo CC $< $@
	@${CC} ${CFLAGS} $< -o $@

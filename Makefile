MAKEFLAGS+=-rR
CC=clang
CFLAGS=-std=c99 -O2 -D_POSIX_C_SOURCE=200809L -D_XOPEN_SOURCE=700 -U_GNU_SOURCE -U_BSD_SOURCE -Weverything -Wno-parentheses -Wno-missing-prototypes -Wno-sign-conversion
all: cat
%: %.c Makefile
	@echo "CC	$<	$@"
	@${CC} ${CFLAGS} $< -o $@
clean:
	rm cat

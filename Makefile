# libhwsunxi shared library

STATIC=libhwsunxi.a
DYNAMIC=libhwsunxi.so

CC = gcc
CFLAGS = -O2 -D_GNU_SOURCE -Wformat=2 -Wall -Wextra -Winline -I. -pipe -fPIC
LIBS = 

SRC = gpio.c

OBJ = $(SRC:.c=.o)

all: $(DYNAMIC)

static: $(STATIC)

$(STATIC): $(OBJ)
	ar rcs $(STATIC) $(OBJ)
	ranlib $(STATIC)
#	@size   $(STATIC)

$(DYNAMIC): $(OBJ)
	$(CC) -shared -Wl,-soname,$(DYNAMIC) -o $(DYNAMIC) $(LIBS) $(OBJ)

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJ) libhwsunxi.*

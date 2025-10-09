CC = g++
SRC = src/main.cpp
OUT = bin/project-pgk

PKG = allegro-5 allegro_main-5 allegro_primitives-5
CFLAGS = $(shell pkg-config --cflags $(PKG))
LDFLAGS = $(shell pkg-config --libs $(PKG))

all: $(OUT)

$(OUT): $(SRC)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf bin

.PHONY: all clean

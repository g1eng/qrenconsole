BIN = qrenconsole
CC ?= g++
CPP = g++
CPPFLAGS += -O
CPPFLAGS += -Wall
PREFIX ?= /

all:
	$(CPP) main.cpp -o $(BIN) $(CPPFLAGS) /lib/x86_64-linux-gnu/libqrencode.so

install:
	install -D -m 755 qrenconsole ${PREFIX}/bin

clean:
	rm -v $(OBJS) $(TARGET)

uninstall:
	install -m 755 qrenconsole ${HOME}/bin

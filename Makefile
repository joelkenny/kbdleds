#Macros
CC = gcc
CFLAGS = -Wall
SRC = kbdleds.c leds.c
OBJ = kbdleds.o leds.o
BIN = kbdleds
SCRIPTS = kbdleds-control kbdleds-server

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(BIN)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -c

clean:
	rm -f $(OBJ)

pristine: clean
	rm -f $(BIN)

install: kbdleds
	install -g root -o root $(BIN) /usr/bin

uninstall:
	rm -f /usr/bin/$(BIN)

install-tools:
	install -g root -o root $(SCRIPTS) /usr/local/etc

uninstall-tools:
	rm -f /usr/local/etc/kbdleds-control
	rm -f /usr/local/etc/kbdleds-server

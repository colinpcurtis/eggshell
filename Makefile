CC=gcc
CFLAGS=-Wall -Wextra
EXEC=shell
OBJ=main.o shell.o

.phony: clean

%.o: %.c %.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

clean:
	rm $(EXEC) $(OBJ)

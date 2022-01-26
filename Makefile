CC=gcc
CFLAGS=-Wall -Wextra -std=c17
EXEC=eggshell
OBJ=main.o parser.o execute.o

.PHONY: clean

%.o: %.c %.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

clean:
	rm $(EXEC) $(OBJ)

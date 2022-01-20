CC=gcc
CFLAGS=
EXEC=shell
OBJ=main.o

.phony: clean

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

clean:
	rm $(EXEC) $(OBJ)

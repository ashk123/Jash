CC=gcc
OBJ_FILES=src/main.o src/cmd.o src/var.o
OUTPUT=jash
headers=-Iinclude

%.o: %.c
	$(CC) $< -c $(headers) -o $@

jash: $(OBJ_FILES)
	$(CC) -o $(OUTPUT) $^ $(headers)

clean:
	rm $(OUTPUT)
	rm -r src/*.o

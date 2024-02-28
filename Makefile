CC=gcc
OBJ_FILES=src/main.o src/cmd.o
OUTPUT=jash

%.o: src/%.c
	$(CC) -c $< -o $@

jash: $(OBJ_FILES)
	$(CC) -o $(OUTPUT) $^

clean:
	rm $(OUTPUT)
	rm -r src/*.o

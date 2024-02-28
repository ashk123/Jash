CC=gcc
OBJ_FILES=src/main.o src/cmd.o
OUTPUT=jash

%.o: src/%.cc
	$(CC) -c $< -o $@

jash: $(OBJ_FILES)
	$(CC) -o $(OUTPUT) $^

clean:
	rm -r src/*.o

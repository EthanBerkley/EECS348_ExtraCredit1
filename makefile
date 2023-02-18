NAMES = main Data
SRC = $(addsuffix .cpp, $(addprefix src/,$(NAMES))) # "main" --> "src/main.cpp"
BIN = $(addsuffix .o, $(addprefix bin/,$(NAMES)))	# "main" --> "bin/main.o"

out: bin/ $(BIN) # recompile whenever any .o file is updated
	g++ -g $(BIN) -o out 

bin/:	# make bin folder if it doesnt exist 
	mkdir bin

./bin/%.o: ./src/%.cpp # recompile .o file when .cpp file is updated
	cc -c -g $< -o $@

clean: # delete any compiled / linked file
	rm -rf bin out
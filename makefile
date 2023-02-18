NAMES = main Data
SRC = $(addsuffix .cpp, $(addprefix src/,$(NAMES)))
BIN = $(addsuffix .o, $(addprefix bin/,$(NAMES)))

out: bin/ $(BIN) 
	g++ -g $(BIN) -o out 

bin/:			
	mkdir bin

./bin/%.o: ./src/%.cpp
	cc -c -g $< -o $@

clean:
	rm -rf bin out
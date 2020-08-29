run: all
	@./bin/main

all: ./bin ./src/main.cpp
	@g++ -o ./bin/main ./src/main.cpp

bin:
	@mkdir -p ./bin

clean:
	@rm -r ./bin

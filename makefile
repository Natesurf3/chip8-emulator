run: all
	@./bin/main

all: ./src/main.cpp
	@mkdir -p ./bin
	@g++ -o ./bin/main ./src/main.cpp

clean:
	@rm -r ./bin

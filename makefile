run: all
	@./bin/main

all: main.cpp
	@mkdir -p ./bin
	@g++ -o ./bin/main main.cpp

clean:
	@rm -r ./bin

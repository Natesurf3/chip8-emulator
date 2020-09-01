clean:
	@rm -r ./bin

bin:
	@mkdir -p ./bin

# ---- main ----
run: ./bin/main
	@./bin/main

./bin/main: ./src/main.cpp
	@g++ -o ./bin/main ./src/main.cpp

# ---- test ----
test: ./bin ./bin/test
	@./bin/test

./bin/test: ./src/test.cpp
	@g++ -o ./bin/test ./src/test.cpp

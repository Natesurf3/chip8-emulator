BIN = ../../bin

clean:
	@rm -r ${BIN}

${BIN}:
	@mkdir -p ${BIN}

# ---- main ----
run: ${BIN}/main
	@${BIN}/main

${BIN}/main: ./main.cpp
	@g++ -o ${BIN}/main ./main.cpp

# ---- test ----
test: ${BIN}/test
	@${BIN}/test

./bin/test: ./src/test.cpp
	@g++ -o ${BIN}/test ./src/test.cpp

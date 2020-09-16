BIN = ../../bin

clean:
	@rm -rf ${BIN}

run: main

${BIN}:
	@mkdir -p ${BIN}

# ---- main ----
main: clean ${BIN} ${BIN}/main
	@${BIN}/main

${BIN}/main: ./main.cpp
	@g++ -o ${BIN}/main ./main.cpp

# ---- test ----
test: clean ${BIN} ${BIN}/test
	@${BIN}/test

${BIN}/test: ./test.cpp
	@g++ -o ${BIN}/test ./test.cpp

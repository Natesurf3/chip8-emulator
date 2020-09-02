BIN = ../../bin

clean:
	@rm -r ${BIN}

run: main

${BIN}:
	@mkdir -p ${BIN}

# ---- main ----
main: ${BIN} ${BIN}/main
	@${BIN}/main

${BIN}/main: ./main.cpp
	@g++ -o ${BIN}/main ./main.cpp

# ---- test ----
test: ${BIN} ${BIN}/test
	@${BIN}/test

${BIN}/test: ./test.cpp
	@g++ -o ${BIN}/test ./test.cpp
